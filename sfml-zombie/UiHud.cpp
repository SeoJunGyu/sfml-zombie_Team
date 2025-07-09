#include "stdafx.h"
#include "UiHud.h"
#include "Player.h"


UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetTextScore(int score)
{
	
	textScore.setString("Score : " + std::to_string(score));
	textScore.setPosition(0, 0);
	textScore.setCharacterSize(50);
	
	Utils::SetOrigin(textScore, Origins::TL);
}

void UiHud::SetTextHighScore(int score)
{
	
	textHighScore.setString("High Score : " + std::to_string(score));
	textHighScore.setPosition(1920, 0);
	textHighScore.setCharacterSize(50);
	Utils::SetOrigin(textHighScore, Origins::TR);
	
}

void UiHud::SetTextWave()
{

	textWave.setString("Wave : " + std::to_string(Variable::wave));
	textWave.setPosition(1400, 1000);
	textWave.setCharacterSize(50);
	Utils::SetOrigin(textWave, Origins::BC);;
}

void UiHud::SetTextZombie(int count)
{
	
	textZombie.setString("Zombie : " + std::to_string(count));
	textZombie.setPosition(1700, 1000);
	textZombie.setCharacterSize(50);
	Utils::SetOrigin(textZombie, Origins::BC);;
}

void UiHud::SetTextBulletCount(int count, int maxCount)
{
	textBullet.setString(std::to_string(count) + " / " + std::to_string(maxCount));
	textBullet.setPosition(200, 1000);
	textBullet.setCharacterSize(50);
	Utils::SetOrigin(textBullet, Origins::BC);
}

void UiHud::SetHpBar(float value)
{
	hpBar.setSize({ hpBarSize.x * value, hpBarSize.y });
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	
}

void UiHud::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	
}

void UiHud::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	
}



void UiHud::Init()
{
	sortingLayer = SortingLayers::UiView;
	sortingOrder = 0;

}

void UiHud::Release()
{
}

void UiHud::Reset()
{

	

	bullets.setTexture(TEXTURE_MGR.Get(BulletsId));
	bullets.setPosition(0, 950);
	textScore.setFont(FONT_MGR.Get(FontId));
	textZombie.setFont(FONT_MGR.Get(FontId));;
	textHighScore.setFont(FONT_MGR.Get(FontId));
	textWave.setFont(FONT_MGR.Get(FontId));
	textBullet.setFont(FONT_MGR.Get(FontId));
	
	SetTextScore(Variable::score);
	SetTextHighScore(Variable::score);
	SetTextWave();
	SetTextZombie(10);
	

	hpBarSize = { 400.f,50.f };
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(hpBarSize);
	Utils::SetOrigin(hpBar, Origins::BL);
	hpBar.setPosition(300, 1000);
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(bullets);
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(textWave);
	window.draw(textZombie);
	window.draw(textBullet);
	window.draw(hpBar);
}