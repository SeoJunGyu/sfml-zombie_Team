#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox()
{
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.f);
}

void HitBox::UpdateTransform(const sf::Transformable& shape, const sf::FloatRect rt)
{
	rect.setSize({ rt.width, rt.height });
	rect.setOutlineColor(sf::Color::Green);
	rect.setPosition(shape.getPosition());
	rect.setRotation(shape.getRotation());
	rect.setScale(shape.getScale());
	rect.setOrigin(shape.getOrigin());
}

void HitBox::Draw(sf::RenderWindow& window)
{
	if (Variable::isDrawHitBox)
	{
		window.draw(rect);
	}
}
