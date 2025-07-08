#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/crosshair.png");

	AddGameObject(new TileMap("TileMap"));
	
	Scene::Init();
	
	
}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);

	Scene::Enter();
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
}

void SceneGame::Exit()
{
}

void SceneGame::Update(float dt)
{
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}
