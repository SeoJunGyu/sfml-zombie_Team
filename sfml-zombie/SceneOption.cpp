#include "stdafx.h"
#include "SceneOption.h"


SceneOption::SceneOption()
	: Scene(SceneIds::Option)
{
}

void SceneOption::Init()
{
	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	option.setTexture(TEXTURE_MGR.Get(texId), true);
	option.setPosition(0.f, 0.f);


	font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	std::vector<std::string> optionStrings = {
		"Fire Rate Boost",
		"Larger Clip (Next Reload Only)",
		"Health Capacity Boost",
		"Faster Movement",
		"Improved Health Drops",
		"Improved Ammo Drops"
	};

	float startY = 200.f;
	float gapY = 120.f;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	for (size_t i = 0; i < optionStrings.size(); ++i)
	{
		sf::Text text;
		text.setFont(font);
		text.setString(optionStrings[i]);
		text.setCharacterSize(70);
		text.setFillColor(sf::Color(149, 204, 164));

		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

		float x = windowSize.x / 2.f;
		float y = startY + i * gapY;
		text.setPosition(x, y);
		optionTexts.push_back(text);
	}


	Scene::Init();
}

void SceneOption::Enter()
{
	SetUpViews();
	Scene::Enter();
}

void SceneOption::Exit()
{
	Scene::Exit();
}

void SceneOption::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2i mousePos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePos, uiView);

	for (size_t i = 0; i < optionTexts.size(); ++i)
	{
		auto& text = optionTexts[i];
		if (text.getGlobalBounds().contains(worldPos))
		{
			text.setFillColor(sf::Color::Yellow); // hover
			text.setScale(1.1f, 1.1f);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				switch (i)
				{
				case 0: Variable::fireRateBoost = true; break;
				case 1: Variable::largerClipNextReload = true; break;
				case 2: Variable::healthBoost = true; break;
				case 3: Variable::fasterMovement = true; break;
				case 4: Variable::betterHealthDrops = true; break;
				case 5: Variable::betterAmmoDrops = true; break;
				}
				SCENE_MGR.ChangeScene(SceneIds::Game);
				break;
			}
		}
		else
		{
			text.setFillColor(sf::Color(149, 204, 164));
			text.setScale(1.0f, 1.0f);
		}
	}
}

void SceneOption::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	resourceLoad();
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);

	option.setTexture(TEXTURE_MGR.Get(texId), true);
	option.setPosition(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	

}

void SceneOption::resourceLoad()
{
	texIds.push_back(texId);
	fontIds.push_back("fonts/zombiecontrol.ttf");
}

void SceneOption::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(option);
	for (auto& text : optionTexts)
	{
		window.draw(text);
	}
}

//Fire Rate Boost, Larger Clip (Next Reload Only, Health Capacity Boost, Faster Movement, Improved Health Drops, Improved Ammo Drops
