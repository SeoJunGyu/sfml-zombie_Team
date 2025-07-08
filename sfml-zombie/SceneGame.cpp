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
				//��Ȱ�� ���� ���ٸ� ���� �߰�
				zombie = (Zombie*)AddGameObject(new Zombie());
				zombie->Init();
			}
			else
			{
				//��Ȱ�� ���� �ִٸ�
				zombie = zombiePool.front(); //�Ҵ�
				zombiePool.pop_front(); //��Ȱ�� ��Ͽ��� ����
				zombie->SetActive(true); //Ȱ��
			}

			zombie->Reset();
			zombie->SetType((Zombie::Type)0);
			zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
			zombieList.push_back(zombie);
		}
	}

	
}
