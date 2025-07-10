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
	texIds.push_back("graphics/blood.png");

	soundPlayer.Load("bgm", "sound/index.m3u8");
	soundPlayer.Load("death", "sound/death.wav");
	soundPlayer.Load("shoot", "sound/shoot.wav");
	soundPlayer.Load("hit", "sound/hit.wav");
	soundPlayer.Load("pickup", "sound/pickup.wav");
	soundPlayer.Load("reload", "sound/reload.wav");

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

	font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	pauseText.setFont(font);
	pauseText.setString("Press Enter To Continue");
	pauseText.setCharacterSize(80);
	pauseText.setFillColor(sf::Color(255, 224, 189));

	sf::FloatRect bounds = pauseText.getLocalBounds();
	pauseText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	float yOffset = 0.f;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	pauseText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + yOffset);

	Scene::Init();
	score = 0;
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);

	if (Variable::wave == 1)
	{
		score = 0;
		player->AllReset();
	}
	
	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
	zombieCount = Variable::wave * 5;
	SpawnZombie(zombieCount);
	SpawnItem(Variable::wave * 5);
	uiHud->SetTextScore(score);
	std::cout << zombieList.size() << std::endl;
}

void SceneGame::Exit()
{
	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	for (Zombie* zombie : zombieErase)
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
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		Variable::wave = 1;
		score = 0;
		player->AllReset();
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		isPlaying = !isPlaying;
	}
	if (!isPlaying)
	{
		return;
	}

	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	worldView.setCenter(player->GetPosition());
	Scene::Update(dt);
	uiHud->SetTextZombie(zombieCount);
	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		if ((*it)->GetTexId() == "graphics/blood.png")
		{
			
			zombieErase.push_back(*it);
			it = zombieList.erase(it);
			zombieCount--;
			score += 10;
			uiHud->SetTextScore(score);
			if (Variable::highScore < score)
			{
				Variable::highScore = score;
				uiHud->SetTextHighScore(Variable::highScore);
			}
		}
		else
		{
			it++;
		}
	}
	if (zombieCount == 0)
	{
		Variable::wave++;
		SCENE_MGR.ChangeScene(SceneIds::Option);
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

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
	if (!isPlaying)
	{
		window.draw(pauseText);
	}
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

		zombie->SetAlive(true);
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

		if (Variable::betterAmmoDrops) ammoWeight += 10;
		if (Variable::betterHealthDrops) healthWeight += 10;

		int totalWeight = ammoWeight + healthWeight + otherWeight;
		int rand = Utils::RandomRange(0, totalWeight);

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

		item->SetType(dropType);
		item->Reset();
		item->SetPosition(Utils::RandomInUnitCircle() * (200.f * Variable::wave));
		itemList.push_back(item); 
	}
}
