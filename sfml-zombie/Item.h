#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

class Item :
    public GameObject
{
public:
	enum Type
	{
		Ammo,
		Health,
		Count,
	};

protected:
	sf::Sprite body;
	std::string texId;

	int value = 0; //��ź�� Ȥ�� ȸ����

	Player* player = nullptr;
	HitBox hitBox;

	Type type = Type::Ammo;

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

	void SetType(Type type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() { return hitBox; }
	void OnInteract(int value);
};

