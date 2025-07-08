#pragma once
#include "Scene.h"

class UiHud;
class SceneGame :  public Scene
{
protected:
	sf::Sprite cursor;
	UiHud* uiHud;
public:
	SceneGame();
	~SceneGame() override;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

