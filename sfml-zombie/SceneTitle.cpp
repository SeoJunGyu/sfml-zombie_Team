#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	background.setTexture(TEXTURE_MGR.Get(texId), true);
	Scene::Init(); //씬 타일틀 init 원래 씬이 가지고 있던 부모를 가져다 쓰는 (원래 못쓰지만)
}

void SceneTitle::Enter()
{
	SetUpViews();
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneTitle::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

void SceneTitle::resourceLoad()
{
	texIds.push_back("graphics/background.png");
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background);
}
