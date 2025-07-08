#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/Bloater.png");
	texIds.push_back("graphics/Chaser.png");
	texIds.push_back("graphics/Crawler.png");
	texIds.push_back("graphics/player.png");

	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; i++)
	{
		zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	
	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);
	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		for (int i = 0; i < 10; i++)
		{
			Zombie* zombie = nullptr;
			if (zombiePool.empty())
			{
				zombie = (Zombie*)AddGameObject(new Zombie());
				zombie->Init();
			}
			else
			{
				zombie = zombiePool.front();
				zombiePool.pop_front();
				zombie->SetActive(true);
			}

			zombie->SetType((Zombie::Type)Utils::RandomRange(0, Zombie::TotalType));
			zombie->Reset();
			zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
			zombieList.push_back(zombie);
		}
	}

	
}
