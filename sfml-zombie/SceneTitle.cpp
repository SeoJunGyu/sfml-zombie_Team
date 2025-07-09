#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	soundPlayer.Load("bgm", "sound/bgm.wav");
	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	background.setTexture(TEXTURE_MGR.Get(texId), true);

	font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	titleText.setFont(font);
	titleText.setString("Game Start");
	titleText.setCharacterSize(80);
	titleText.setFillColor(sf::Color(255, 224, 189));

	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	float yOffset = 300.f;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	titleText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f  + yOffset);
	Scene::Init(); //씬 타일틀 init 원래 씬이 가지고 있던 부모를 가져다 쓰는 (원래 못쓰지만)
}

void SceneTitle::Enter()
{
	soundPlayer.Play("bgm");
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

	blinkTimer += dt;
	if (titleText.getGlobalBounds().contains(worldPos))
	{
		Visible = true;
		titleText.setFillColor(sf::Color::Red);
		titleText.setScale(1.1f, 1.1f);
	}
	else
	{
		if (blinkTimer >= blinkInterval)
		{
			blinkTimer = 0.f;
			titleText.setFillColor(sf::Color(255, 224, 189));
			titleText.setScale(1.0f, 1.0f);
			Visible = !Visible;
		}
		
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

	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	background.setTexture(TEXTURE_MGR.Get(texId), true);

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
	if (Visible)
	{
		window.draw(titleText);
	}
}

