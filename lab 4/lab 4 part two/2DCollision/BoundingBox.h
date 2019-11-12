#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <SFML/Graphics.hpp>

class BoundingBox
{
public:
	BoundingBox();

	sf::RectangleShape boxBody;
	float width;
	float height;
	sf::Vector2f Position;
	
};

#endif