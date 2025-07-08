#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

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
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}
	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f , 0.f };
	look = { 1.f , 0.f }; //스트라이트의 기본이 오른쪽으로 바라보고 있는 상태
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f) //거리 측정 속도 계산 (백터의 길이)
	{
		Utils::Normalize(direction); //방향 
	}
	SetPosition(position + direction * speed * dt);
	sf::Vector2i mousePos = InputMgr::GetMousePosition();

	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
