#pragma once
#include "Scene.h"

class Zombie;
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


	sf::Sprite cursor;
	UiHud* uiHud;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombie(int count);
};

