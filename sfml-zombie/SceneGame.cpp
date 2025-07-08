#include "stdafx.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "UiHud.h"

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
	texIds.push_back("graphics/ammo_icon.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");

	
	AddGameObject(new TileMap("TileMap"));
	
	uiHud = (UiHud*)AddGameObject(new UiHud("UiHud"));
	
	Scene::Init();
	
	
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * .5f);

	Scene::Enter();
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame::Exit()
{
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);
}
