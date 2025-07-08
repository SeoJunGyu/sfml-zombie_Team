#include "stdafx.h"
#include "Bullet.h"
Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	gameObject.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	gameObject.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	gameObject.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	gameObject.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(gameObject, preset);
	}
}

void Bullet::Init()
{
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
}

void Bullet::Update(float dt)
{
}

void Bullet::Draw(sf::RenderWindow& window)
{
}