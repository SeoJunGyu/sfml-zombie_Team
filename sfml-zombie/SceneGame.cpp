#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "UiHud.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/ammo_icon.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");

	
	AddGameObject(new TileMap("TileMap"));
	
	uiHud = (UiHud*)AddGameObject(new UiHud("UiHud"));
	
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");

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
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);

	Scene::Enter();
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame::Exit()
{
	//Ȱ�� ���� ��Ȱ��ȭ
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
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	Scene::Update(dt);
	Scene::Update(dt);
	//std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		//��Ȱ��ȭ�Ǿ��ִٸ�
		if (!(*it)->GetActive())
		{
			//��Ȱ��ȭ ��Ͽ� �ְ�, Ȱ�� ��Ͽ��� �����.
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
	window.setView(uiView);
	window.draw(cursor);
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
