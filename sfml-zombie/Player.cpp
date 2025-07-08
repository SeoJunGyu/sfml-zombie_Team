#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"

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
	sortingLayer = SortingLayers::ForeGround;
	sortingOrder = 0;
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); //다운 캐스팅 
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
	look = { 1.f , 0.f }; //스트라이트의 기본이 오른쪽으로 바라보고 있는 상태
}


void Player::Update(float dt)
{
	auto it = bulletList.begin();
	while ( it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it); //요소이기때문에 포인터연산자 필요
			bulletList.erase(it);
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
	SetPosition(position + direction * speed * dt);
	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		Shoot();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
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
	bullet->Fire(position + look * 10.f, look, 1000.f, 10);

	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);


}
