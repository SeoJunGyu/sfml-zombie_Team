#include "stdafx.h"
#include "SceneGame.h"
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
				//비활성 좀비가 없다면 새로 추가
				zombie = (Zombie*)AddGameObject(new Zombie());
				zombie->Init();
			}
			else
			{
				//비활성 좀비가 있다면
				zombie = zombiePool.front(); //할당
				zombiePool.pop_front(); //비활성 목록에서 제거
				zombie->SetActive(true); //활성
			}

			zombie->Reset();
			zombie->SetType((Zombie::Type)0);
			zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
			zombieList.push_back(zombie);
		}
	}

	
}