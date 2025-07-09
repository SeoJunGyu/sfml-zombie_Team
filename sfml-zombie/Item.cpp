#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "UiHud.h"

Item::Item(const std::string& name)
	: GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	//SetType(type);
}

void Item::Release()
{
}

void Item::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");
	uiHud = (UiHud*)SCENE_MGR.GetCurrentScene()->FindGameObject("UiHud");

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void Item::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());

	if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
	{
		OnInteract(value);
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Item::SetType(Type type)
{
	this->type = type;
	switch (type)
	{
	case Item::Ammo:
		texId = "graphics/ammo_pickup.png";
		value = 10;
		break;
	case Item::Health:
		texId = "graphics/health_pickup.png";
		value = 50;
		break;
	}
}

void Item::OnInteract(int value)
{
	switch (type)
	{
	case Type::Ammo:
		player->SetAmmo(value);
		uiHud->SetTextBulletCount(player->GetAmmo(), player->GetMaxAmmo());
		break;

	case Type::Health:
		if (player->GetHp() + value > player->GetMaxHp())
		{
			int tmp = player->GetMaxHp() - player->GetHp();
			player->SetHp(tmp);
			uiHud->SetHpBar((float)player->GetHp() / player->GetMaxHp());
		}
		else
		{
			player->SetHp(value);
			uiHud->SetHpBar((float)player->GetHp() / player->GetMaxHp());
		}
		
		break;
	}
	SetActive(false);
}
