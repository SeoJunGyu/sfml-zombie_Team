#pragma once
#include "Scene.h"

class Zombie;
class Item;
class Player;
class UiHud;

class SceneGame :
    public Scene
{
protected:
	Zombie* zombie = nullptr;
	Player* player = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

	std::list<Item*> itemList;
	std::list<Item*> itemPool;

	sf::Sprite cursor;
	UiHud* uiHud;
	int zombieCount = 0;
	int score = 0;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombie(int count);
	void SpawnItem(int count);
	const std::list<Zombie*>& GetZombies() const
	{
		return zombieList;
	}
};

