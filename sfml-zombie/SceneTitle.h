#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:
	sf::Sprite background;
	std::string texId = "graphics/background.png";

	sf::Text titleText;
	sf::Font font; 

public:
	SceneTitle();

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Exit() override;
	void SetUpViews();
	void resourceLoad();
	virtual void Draw(sf::RenderWindow& window) override;
};

