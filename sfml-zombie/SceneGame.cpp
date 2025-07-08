#include "stdafx.h"
#include "SceneGame.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	

}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);
}

void SceneGame::Exit()
{
}

void SceneGame::Update(float dt)
{
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	
	
}
