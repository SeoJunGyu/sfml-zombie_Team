#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{
public:
	enum Type
	{
		ammo,
		health,
		count,
	};

protected:
	sf::Sprite body;
	std::string texId;

	int value = 0; //장탄수 혹은 회복값

	

public:
	Item(const std::string& name = "");
	virtual ~Item() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

