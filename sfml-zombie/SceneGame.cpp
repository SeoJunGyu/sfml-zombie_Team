#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "UiHud.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Item.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/ammo_icon.png");
	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/bullet.png");

	fontIds.push_back("fonts/zombiecontrol.ttf");

	AddGameObject(new TileMap("TileMap"));

	uiHud = (UiHud*)AddGameObject(new UiHud("UiHud"));

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
	SpawnZombie(Variable::wave * 5);
	SpawnItem(Variable::wave * 5);
}

void SceneGame::Exit()
{
	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	for (Item* item : itemList)
	{
		item->SetActive(false);
		itemPool.push_back(item);
	}
	zombieList.clear();
	itemList.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		if (!(*it)->GetActive())
		{
			zombiePool.push_back(*it);
			it = zombieList.erase(it);
		}
		else
		{
			it++;
		}
	}

	auto itItem = itemList.begin();
	while (itItem != itemList.end())
	{
		if (!(*itItem)->GetActive())
		{
			itemPool.push_back(*itItem);
			itItem = itemList.erase(itItem);
		}
		else
		{
			itItem++;
		}
	}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SpawnZombie(Variable::wave * 5);
	//	SpawnItem(Variable::wave * 5);
	//}

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
		zombie->SetPosition(Utils::RandomInUnitCircle() * (200.f * Variable::wave));
		zombieList.push_back(zombie);
	}
}

void SceneGame::SpawnItem(int count)
{

	for (int i = 0; i < count; i++)
	{
		Item* item = nullptr;
		if (itemPool.empty())
		{
			item = (Item*)AddGameObject(new Item());
			item->Init();
		}
		else
		{
			item = itemPool.front();
			itemPool.pop_front();
			item->SetActive(true);
		}

		int ammoWeight = 6;
		int healthWeight = 6;
		int otherWeight = 2;

		if (Variable::betterAmmoDrops) ammoWeight += 14;
		if (Variable::betterHealthDrops) healthWeight += 14;

		int totalWeight = ammoWeight + healthWeight + otherWeight;
		int rand = Utils::RandomRange(0, totalWeight);

		std::cout << "[SpawnItem] ammoWeight=" << ammoWeight
			<< ", healthWeight=" << healthWeight
			<< ", otherWeight=" << otherWeight
			<< ", totalWeight=" << totalWeight
			<< ", rand=" << rand << std::endl;

		Item::Type dropType = Item::Type::None;

		if (rand < ammoWeight)
		{
			dropType = Item::Type::Ammo;
		}
		else if (rand < ammoWeight + healthWeight)
		{
			dropType = Item::Type::Health;
		}
		else
		{
			dropType = (Item::Type)Utils::RandomRange(0, Item::Type::Count);
		}

		std::cout << "[SpawnItem] DropType=" << (int)dropType << std::endl;

		item->SetType(dropType);
		item->Reset();
		item->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		itemList.push_back(item); 
	}
}
