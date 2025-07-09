#pragma once
#include "Scene.h"
#include "SoundPlayer.h"
class SceneTitle :
    public Scene
{
protected:
	sf::Sprite background;
	std::string texId = "graphics/background.png";

	sf::Text titleText;
	sf::Font font; 

	SoundPlayer soundPlayer;

	float blinkInterval = 0.5f;
	float blinkTimer = 0.f;
	bool Visible = true;

	sf::RectangleShape fadeRect;
	int fadeAlpha = 255;
	float fadeSpeed = 255.f;

	bool fadeIn = true;
	bool fadeOut = false;

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

