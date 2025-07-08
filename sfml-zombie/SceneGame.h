#pragma once
#include "Scene.h"

class Player;

class SceneGame :
    public Scene
{
protected:
	Player* player = nullptr; //기본값을 할당 nullptr로 쓰레기값 방지 

public:
	SceneGame(const std::string& name = "");
	virtual ~SceneGame() = default;

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

