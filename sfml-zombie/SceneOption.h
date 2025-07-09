#pragma once
#include "Scene.h"
class SceneOption :
    public Scene
{
protected:
	sf::Sprite option;
	std::string texId = "graphics/option.png";

	std::vector<sf::Text> optionTexts;
	sf::Font font;


public:
	SceneOption();

	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Exit() override;
	void SetUpViews();
	void resourceLoad();
	virtual void Draw(sf::RenderWindow& window) override;
};

