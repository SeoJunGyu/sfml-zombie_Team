#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "TileMap.h"
#include "UiHud.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}
void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::Init()
{
	soundPlayer.Load("shoot", "sound/shoot.wav");
	soundPlayer.Load("reload", "sound/reload.wav");
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); //�ٿ� ĳ���� 
	}
	else
	{
		sceneGame = nullptr;
	}

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f , 0.f };
	look = { 1.f , 0.f };

	hp = maxHp;
	look = { 1.f , 0.f };
	if (Variable::fireRateBoost)
	{
		attackInterval = Utils::Clamp(attackInterval - 0.1f, 0.1f, 1.f);  // 발사 간격 빨라짐
		Variable::fireRateBoost = false;
	} 

	if (Variable::largerClipNextReload)
	{
		maxReload += 3;  // 다음 리로드에 장탄수 증가
		Variable::largerClipNextReload = false;
	}

	if (Variable::healthBoost)
	{
		maxHp += 500;
		hp = maxHp;
		Variable::healthBoost = false;
	}

	if (Variable::fasterMovement)
	{
		speed += 200.f;
		Variable::fasterMovement = false;
	}

	// UI 연결
	uihud = (UiHud*)SCENE_MGR.GetCurrentScene()->FindGameObject("UiHud");
	if (uihud)
	{
		uihud->SetTextBulletCount(ammo, maxAmmo);
		uihud->SetHpBar((float)hp / maxHp);
	}

	tileMap = (TileMap*)SCENE_MGR.GetCurrentScene()->FindGameObject("TileMap");
}


void Player::Update(float dt)
{
	sf::RectangleShape mapBounds = tileMap->GetBounds();
	auto it = bulletList.begin();
	while ( it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else 
		{
			++it;
		}
	}

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2f pos = position + direction * speed * dt;
	if (!Utils::CheckCollision(mapBounds, hitBox.rect))
	{
		pos.x = Utils::Clamp(pos.x, mapBounds.getGlobalBounds().left -25, mapBounds.getGlobalBounds().left + mapBounds.getGlobalBounds().width  + 25);
		pos.y = Utils::Clamp(pos.y, mapBounds.getGlobalBounds().top -25, mapBounds.getGlobalBounds().top + mapBounds.getGlobalBounds().height + 25);

	}
	SetPosition(pos);
	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

	attackTimer += dt;
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && attackTimer > attackInterval)
	{
		if (ammo > 0)
		{
			soundPlayer.Play("shoot");
			Shoot();
			attackTimer = 0.f;
			ammo--;
			uihud->SetTextBulletCount(ammo, maxAmmo);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::OnDamage(int damage)
{
	if (!IsAlive())
	{
		return;
	}

	uihud->SetHpBar((float)hp/maxHp);
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		Variable::wave = 1;
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}

void Player::AllReset()
{
	speed = 500.f;
	maxHp = 100;
	maxAmmo = 3;
	ammo = 3;
	maxReload = 6;
	attackInterval = 1.f;
}

void Player::Reload()
{
	if (maxAmmo > 0)
	{
		if (maxReload - ammo > maxAmmo)
		{
			soundPlayer.Play("reload");
			ammo += maxAmmo;
			maxAmmo = 0;
			uihud->SetTextBulletCount(ammo, maxAmmo);
		}
		else
		{
			soundPlayer.Play("reload");
			maxAmmo -= maxReload - ammo;
			ammo += maxReload - ammo;
			uihud->SetTextBulletCount(ammo, maxAmmo);
		}
	}
}

void Player::Shoot()
{
	Bullet* bullet = nullptr;
	if (bulletPool.empty())
	{
		bullet = new Bullet;
		bullet->Init();
	}
	else
	{
		bullet = bulletPool.front();
		bulletPool.pop_front();
		bullet->SetActive(true);
	}
	
	bullet->Reset();
	bullet->Fire(position + look * 10.f, look, 1000.f, 100);

	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);
	

}
