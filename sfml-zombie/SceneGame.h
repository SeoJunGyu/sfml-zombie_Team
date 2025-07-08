#pragma once
#include "Scene.h"

class Player;

class SceneGame :
    public Scene
{
protected:
	Player* player = nullptr; //�⺻���� �Ҵ� nullptr�� �����Ⱚ ���� 

public:
	SceneGame(const std::string& name = "");
	virtual ~SceneGame() = default;

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

