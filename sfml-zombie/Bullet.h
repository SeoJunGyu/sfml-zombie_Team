#pragma once
#include "GameObject.h"]
#include "HitBox.h"

class Zombie;
class SceneGame;
class Bullet :
    public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/bullet.png";

	sf::Vector2f direction;
	float speed = 0.f;
	int damage = 0;

	SceneGame* sceneGame;	
	Zombie* zombie;
	HitBox hitbox;

public:
	Bullet(const std::string& name = "");
	virtual ~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Fire(const sf::Vector2f pos, const sf::Vector2f dir, float s, int d);

	HitBox& GetHitbox()
	{
		return hitbox;
	}
};

