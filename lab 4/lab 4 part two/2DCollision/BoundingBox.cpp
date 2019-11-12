#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	width = 30.0;
	height = 30.0;
	
	boxBody.setSize(sf::Vector2f(width, height));
	boxBody.setPosition(10, 10);
	boxBody.setFillColor(sf::Color::Black);
	boxBody.setOutlineColor(sf::Color::White);
	boxBody.setOutlineThickness(3);
}
