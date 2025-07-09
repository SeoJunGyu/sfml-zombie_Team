#pragma once
#include "GameObject.h"



class UiHud : public GameObject
{
protected:
	std::string FontId = "fonts/zombiecontrol.ttf";
	std::string BulletsId = "graphics/ammo_icon.png";

	sf::Text textScore;
	sf::Text textHighScore;
	sf::Text textBullet;
	sf::Text textWave;
	sf::Text textZombie;

	sf::Sprite bullets;
	sf::RectangleShape hpBar;


	sf::Vector2f hpBarSize;


public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetTextScore(int score);
	void SetTextHighScore(int score);
	void SetTextWave();
	void SetTextZombie(int count);
	void SetTextBulletCount(int count, int maxMount);
	void SetHpBar(float value);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

