#pragma once
#include "Scene.h"

class Zombie;
class Player;

class SceneGame :
    public Scene
{
protected:
	Zombie* zombie = nullptr;

	std::list<Zombie*> zombieList; //Ȱ�� ����
	std::list<Zombie*> zombiePool; //��Ȱ�� ����

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	Player* player = nullptr; //�⺻���� �Ҵ� nullptr�� �����Ⱚ ���� 
};

