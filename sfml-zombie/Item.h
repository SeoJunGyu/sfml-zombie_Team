#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "SoundPlayer.h"

class Player;
class UiHud;

class Item :
    public GameObject
{
public:
	enum Type
	{
		Ammo,
		Health,
		None,
		Count,
	};
	static const int TypeCount = 3;

protected:
	sf::Sprite body;
	std::string texId;

	int value = 0; //��ź�� Ȥ�� ȸ����

	Player* player = nullptr;
	UiHud* uiHud = nullptr;
	HitBox hitBox;

	Type type = Type::Ammo;

	SoundPlayer soundPlayer;

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
	Type GetType() const { return type; }
	void SetValue(int value) { this->value = value; }
	int GetValue() const { return value; }

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

