#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

class Zombie :
    public GameObject
{
public:
	enum Type
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalType = 3;

protected:
	sf::Sprite body;
	std::string texId;

	sf::Vector2f direction;
	float speed = 0.f;
	int maxHp = 100;
	int hp = 0;
	int damage = 0;

	Player* player = nullptr;
	HitBox hitBox;

	Type type = Type::Bloater;

public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

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

	void SetType(Type type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
};

