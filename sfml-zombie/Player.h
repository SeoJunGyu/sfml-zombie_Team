#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class Bullet;
class TileMap;
class UiHud;

class Player :
    public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	SceneGame* sceneGame = nullptr;
	HitBox hitBox;

	float speed = 500.f;
	int maxHp = 1000;
	int hp = 0;

	int maxAmmo = 3;
	int ammo = 3;
	int maxReload = 6;

	std::list<Bullet*>bulletList;
	std::list<Bullet*>bulletPool;
	UiHud* uihud;

	float attacInterval = 0.1f;
	float attackTimer = 0.f;

public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

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

	void Shoot();
	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() { return hitBox; }
	void SetHp(int hp) { this->hp = hp; }
	int GetHp() const { return hp; }
	void SetAmmo(int ammo) { maxAmmo += ammo; }
	int GetAmmo() const { return ammo; }
	void OnDamage(int damage);

	bool IsAlive() { return hp > 0; }
};

