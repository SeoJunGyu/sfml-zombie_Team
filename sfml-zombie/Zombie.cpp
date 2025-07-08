#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::ForeGround;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetOrigin({ 0.f, 0.f });

	hp = maxHp;
}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - position);
	SetRotation(Utils::Angle(direction));
	SetPosition(GetPosition() + direction * speed * dt);

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Zombie::SetType(Type type)
{
	switch (type)
	{
	case Zombie::Bloater:
		texId = "graphics/Bloater.png";
		speed = 100.f;
		maxHp = 300;
		damage = 200;
		break;
	case Zombie::Chaser:
		texId = "graphics/Bloater.png";
		speed = 300.f;
		maxHp = 100;
		damage = 100;
		break;
	case Zombie::Crawler:
		texId = "graphics/Bloater.png";
		speed = 100.f;
		maxHp = 50;
		damage = 300;
		break;
	}
}
