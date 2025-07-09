#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"


Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::ForeGround;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); //다운 캐스팅 
	}
	else
	{
		sceneGame = nullptr;
	}

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::ML);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	direction = { 0.f, 0.f };
	speed = 0.f;
	damage = 0;

}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	hitbox.UpdateTransform(body, GetLocalBounds());

	const auto list = sceneGame->GetZombies();

	for (auto zombie : list)
	{
		if (Utils::CheckCollision(hitbox.rect, zombie->GetHitBox().rect))
		{
			SetActive(false);
			zombie->OnDamage(damage);
			break;
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Bullet::Fire(const sf::Vector2f pos, const sf::Vector2f dir, float s, int d)
{
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
}
