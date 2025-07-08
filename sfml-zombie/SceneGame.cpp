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
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
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

void SceneGame::Exit()
{
	//활성 좀비 비활성화
	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	//std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		//비활성화되어있다면
		if (!(*it)->GetActive())
		{
			//비활성화 목록에 넣고, 활성 목록에서 지운다.
			zombiePool.push_back(*it);
			zombieList.erase(it);
		}
		else
		{
			it++;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombie(10);
	}

	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SpawnZombie(int count)
{
	for (int i = 0; i < count; i++)
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
