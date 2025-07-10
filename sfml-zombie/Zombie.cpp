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
	soundPlayer.Load("hit", "sound/hit.wav");
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	barActive = false;

	Utils::SetOrigin(hpBar,Origins::ML);
	hpBar.setPosition(position);
	hpBar.setFillColor(sf::Color::Red);

	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	isAlive = true;

	switch (type)
	{
	case Zombie::Bloater:
		texId = "graphics/bloater.png";
		break;
	case Zombie::Chaser:
		texId = "graphics/chaser.png";
		break;
	case Zombie::Crawler:
		texId = "graphics/crawler.png";
		break;
	}

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	hp = maxHp;
	attackTimer = 0.f;
}

void Zombie::Update(float dt)
{
	if (IsAlive())
	{
		if (Utils::Distance(player->GetPosition(), GetPosition()) >= 10.f)
		{
			direction = Utils::GetNormal(player->GetPosition() - GetPosition());
			SetRotation(Utils::Angle(direction));
			SetPosition(GetPosition() + direction * speed * dt);
		}

		hitBox.UpdateTransform(body, GetLocalBounds());

		attackTimer += dt;
		if (attackTimer > attackInterval)
		{
			if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
			{
				soundPlayer.Play("hit");
				player->OnDamage(damage);
				attackTimer = 0.f;
			}
		}
	}
	hpBar.setPosition(GetPosition());
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (barActive)
	{
		window.draw(hpBar);
	}
	hitBox.Draw(window);
}

void Zombie::SetType(Type type)
{
	this->type = type;
	switch (type)
	{
	case Zombie::Bloater:
		texId = "graphics/bloater.png";
		speed = 50.f;
		maxHp = 300;
		damage = 20;
		attackInterval = 1.f;
		break;
	case Zombie::Chaser:
		texId = "graphics/chaser.png";
		speed = 100.f;
		maxHp = 100;
		damage = 10;
		attackInterval = 1.f;
		break;
	case Zombie::Crawler:
		texId = "graphics/crawler.png";
		speed = 100.f;
		maxHp = 50;
		damage = 10;
		attackInterval = 1.f;
		break;
	}
}

void Zombie::OnDamage(int damage)
{
	if (!IsAlive())
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		hp = 0;
		isAlive = false;
		texId = "graphics/blood.png";
		body.setTexture(TEXTURE_MGR.Get(texId));
	}
}

void Zombie::SetIsHpVisibal()
{
	barActive = true;
}

//void Zombie::HpSetSize()
//{
//	hpBar.setSize()
//}
