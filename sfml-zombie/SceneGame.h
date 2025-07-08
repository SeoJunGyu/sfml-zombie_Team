#pragma once
#include "Scene.h"

class Zombie;

class SceneGame :
    public Scene
{
protected:
	Zombie* zombie = nullptr;

	std::list<Zombie*> zombieList; //활성 좀비
	std::list<Zombie*> zombiePool; //비활성 좀비

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

