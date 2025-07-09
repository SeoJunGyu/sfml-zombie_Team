#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	background.setTexture(TEXTURE_MGR.Get(texId), true);

	font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	titleText.setFont(font);
	titleText.setString("Game Start");
	titleText.setCharacterSize(200);
	titleText.setFillColor(sf::Color::White);

	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	titleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
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

	sf::Vector2i mousePos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePos, uiView);

	if (titleText.getGlobalBounds().contains(worldPos))
	{
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setScale(1.1f, 1.1f);
	}
	else
	{
		titleText.setFillColor(sf::Color::White);
		titleText.setScale(1.0f, 1.0f);
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (titleText.getGlobalBounds().contains(worldPos))
		{
			SCENE_MGR.ChangeScene(SceneIds::Option);
		}
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
	fontIds.push_back("fonts/zombiecontrol.ttf");
	texIds.push_back(texId);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background);
	window.draw(titleText);
}

