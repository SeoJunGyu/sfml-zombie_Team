#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame(const std::string& name)
	: Scene(SceneIds::Game)
{
}


void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");

	player = (Player*)AddGameObject(new Player("Player"));

	//player->SetPosition({ 960.f, 540.f });

}

void SceneGame::Release()
{
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
