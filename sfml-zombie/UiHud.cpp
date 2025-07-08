#include "stdafx.h"
#include "UiHud.h"


UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetTextScore(int score)
{
	textScore.setFont(FONT_MGR.Get(FontId));
	textScore.setString("Score : " + std::to_string(score));
	textScore.setPosition(0, 0);
	textScore.setCharacterSize(50);
	
	Utils::SetOrigin(textHighScore, Origins::TL);
}

void UiHud::SetTextHighScore(int score)
{
	textHighScore.setFont(FONT_MGR.Get(FontId));
	textHighScore.setString("High Score : " + std::to_string(score));
	textHighScore.setPosition(1920, 0);
	textHighScore.setCharacterSize(50);
	Utils::SetOrigin(textHighScore, Origins::TR);
	
}

void UiHud::SetTextWave()
{
	textWave.setFont(FONT_MGR.Get(FontId));
	textWave.setString("Wave : " + std::to_string(Variables::wave));
	textWave.setPosition(1400, 1000);
	textWave.setCharacterSize(50);
	Utils::SetOrigin(textWave, Origins::BC);;
}

void UiHud::SetTextZombie(int count)
{
	textZombieCount.setFont(FONT_MGR.Get(FontId));;
	textZombieCount.setString("Zombie : " + std::to_string(count));
	textZombieCount.setPosition(1700, 1000);
	textZombieCount.setCharacterSize(50);
	Utils::SetOrigin(textZombieCount, Origins::BC);;
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

	
	SetTextScore(Variables::score);
	
	SetTextHighScore(Variables::score);
	SetTextWave();
	SetTextZombie(10);
	
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
	window.draw(textZombieCount);
}