#pragma once
#include "Scene.h"

class Zombie;
class Player;

class SceneGame :
    public Scene
{
protected:
	Zombie* zombie = nullptr;
	Player* player = nullptr;

	std::list<Zombie*> zombieList;
	std::list<Zombie*> zombiePool;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	const std::list<Zombie*>& GetZombies() const
	{
		return zombieList;
	}

	void SpawnZombie(int count);
};

