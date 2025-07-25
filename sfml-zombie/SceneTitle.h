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

