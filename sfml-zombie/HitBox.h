#pragma once
class HitBox
{
public:
	HitBox();

	sf::RectangleShape rect;

	void UpdateTransform(const sf::Transformable& shape, const sf::FloatRect rt);
	void Draw(sf::RenderWindow& window);
};

