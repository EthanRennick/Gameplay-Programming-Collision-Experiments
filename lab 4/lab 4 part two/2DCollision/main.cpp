#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>
#include "BoundingBox.h"

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	BoundingBox boundBox;
	boundBox.boxBody.setSize(sf::Vector2f(90, 90));

	BoundingBox boundBox2;
	boundBox2.boxBody.setSize(sf::Vector2f(90, 90));

	//making a capsule
	sf::CircleShape capsuleBottom;
	sf::CircleShape capsuleCap;
	sf::RectangleShape capsuleBody;

	capsuleCap.setRadius(10);
	capsuleBottom.setRadius(10);
	capsuleBody.setSize(sf::Vector2f(20, 40));

	capsuleCap.setFillColor(sf::Color::Black);
	capsuleCap.setOutlineColor(sf::Color::White);
	capsuleCap.setOutlineThickness(3);

	capsuleBottom.setFillColor(sf::Color::Black);
	capsuleBottom.setOutlineColor(sf::Color::White);
	capsuleBottom.setOutlineThickness(3);

	capsuleBody.setFillColor(sf::Color::Black);
	capsuleBody.setOutlineColor(sf::Color::White);
	capsuleBody.setOutlineThickness(3);

	capsuleCap.setPosition(50, 10);
	capsuleBody.setPosition(50, 20);
	capsuleBottom.setPosition(50, 50);

	c2Capsule capsule;
	capsule.a = c2V(capsuleBody.getPosition().x, capsuleBody.getPosition().y);
	capsule.b = c2V(capsuleBody.getPosition().x + 20, capsuleBody.getPosition().y + 40);
	capsule.r = 10;

	sf::Vector2f lineA {180, 10};
	sf::Vector2f lineB{ 180, 50 };

	sf::Vector2f dv = lineB - lineA;

	float normalised = 0.0f;

	normalised = sqrt((dv.x * dv.x) + (dv.y * dv.y));
	sf::Vector2f unit;
	unit = { dv / normalised };

	sf::Vertex ray[] =
	{
		sf::Vertex(lineA),
		sf::Vertex(lineB)
	};

	c2Raycast raycast;
	c2Ray ray1;
	ray1.p = { lineA.x,lineA.y };
	ray1.t = normalised;
	ray1.d = { unit.x,unit.y };


	

	//Polygon
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(100, 20));
	triangle.setPoint(1, sf::Vector2f(100, 60));
	triangle.setPoint(2, sf::Vector2f(150, 40));
	triangle.setOutlineColor(sf::Color::White);
	triangle.setOutlineThickness(3);
	triangle.setFillColor(sf::Color::Black);


	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	//bool to control which shape we are
	bool circle = false;
	bool box = true;

	//circle
	c2Circle circleman;
	c2v circlePos;
	circlePos.x = 200;
	circlePos.y = 20;
	circleman.p = circlePos;
	circleman.r = 9;

	sf::CircleShape circleBro;
	circleBro.setPosition(200,20);
	circleBro.setFillColor(sf::Color::Black);
	circleBro.setOutlineColor(sf::Color::White);
	circleBro.setOutlineThickness(3);
	circleBro.setRadius(9);

	//circle
	c2Circle circleman2;
	c2v circlePos2;
	circlePos2.x = 250;
	circlePos2.y = 20;
	circleman2.p = circlePos2;
	circleman2.r = 9;

	sf::CircleShape circleBro2;
	circleBro2.setPosition(250, 20);
	circleBro2.setFillColor(sf::Color::Black);
	circleBro2.setOutlineColor(sf::Color::White);
	circleBro2.setOutlineThickness(3);
	circleBro2.setRadius(9);
	
	


	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject &player = Player(player_animated_sprite);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);

	player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));

	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		if (!box)
		{
			circlePos.x = sf::Mouse::getPosition(window).x;
			circlePos.y = sf::Mouse::getPosition(window).y;
			circleman.p = circlePos;

			circleBro.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		}
		else
		{
			circlePos.x = 200;
			circlePos.y = 20;
			circleman.p = circlePos;
			circleBro.setPosition(200, 20);
		}
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (box)
					{
						circle = true;
						box = false;
					}
					else
					{
						circle = false;
						box = true;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		boundBox.boxBody.setPosition(player.getAnimatedSprite().getPosition().x -3, player.getAnimatedSprite().getPosition().y - 3);
		boundBox2.boxBody.setPosition(npc.getAnimatedSprite().getPosition().x - 3, npc.getAnimatedSprite().getPosition().y - 3);

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		if (box)
		{
			result = c2AABBtoAABB(aabb_player, aabb_npc);
			if (result) {
				boundBox.boxBody.setOutlineColor(sf::Color(255, 0, 0));
				boundBox2.boxBody.setOutlineColor(sf::Color(255, 0, 0));
			}
			else {
				boundBox.boxBody.setOutlineColor(sf::Color::White);
				boundBox2.boxBody.setOutlineColor(sf::Color::White);

			}

			result = c2AABBtoCapsule(aabb_player, capsule);
			if (result)
			{
				capsuleCap.setOutlineColor(sf::Color::Red);
				capsuleBody.setOutlineColor(sf::Color::Red);
				capsuleBottom.setOutlineColor(sf::Color::Red);
			}
			else
			{
				capsuleCap.setOutlineColor(sf::Color::White);
				capsuleBody.setOutlineColor(sf::Color::White);
				capsuleBottom.setOutlineColor(sf::Color::White);
			}
			if (boundBox.boxBody.getGlobalBounds().intersects(triangle.getGlobalBounds()))
			{
				triangle.setOutlineColor(sf::Color::Red);
			}
			else
			{
				triangle.setOutlineColor(sf::Color::White);
			}
			result = c2RaytoAABB(ray1, aabb_player, &raycast);
			if (result)
			{
				ray->color = (sf::Color::Red);
			}
			else
			{
				ray->color = (sf::Color::White);
			}

			result = c2CircletoAABB(circleman, aabb_player);
			if (result)
			{
				circleBro.setOutlineColor(sf::Color::Red);
			}
			else
			{
				circleBro.setOutlineColor(sf::Color::White);
			}
		}
		
		if (circle)
		{
			result = c2CircletoAABB(circleman, aabb_npc);
			if (result)
			{
				boundBox2.boxBody.setOutlineColor(sf::Color::Red);
			}
			else
			{
				boundBox2.boxBody.setOutlineColor(sf::Color::White);
			}

			result = c2CircletoCircle(circleman, circleman2);
			if (result)
			{
				circleBro2.setOutlineColor(sf::Color::Red);
			}
			else
			{
				circleBro2.setOutlineColor(sf::Color::White);
			}

			result = c2RaytoCircle(ray1, circleman, &raycast);
			if (result)
			{
				ray->color = (sf::Color::Red);
			}
			else
			{
				ray->color = (sf::Color::White);
			}

			result = c2CircletoCapsule(circleman, capsule);
			if (result)
			{
				capsuleCap.setOutlineColor(sf::Color::Red);
				capsuleBody.setOutlineColor(sf::Color::Red);
				capsuleBottom.setOutlineColor(sf::Color::Red);
			}
			else
			{
				capsuleCap.setOutlineColor(sf::Color::White);
				capsuleBody.setOutlineColor(sf::Color::White);
				capsuleBottom.setOutlineColor(sf::Color::White);
			}
		}
		
		
	

		// Clear screen
		window.clear();
		if(box)
		{
			window.draw(boundBox.boxBody);
		}
		window.draw(boundBox2.boxBody);

		window.draw(capsuleCap);
		window.draw(capsuleBottom);
		window.draw(capsuleBody);

		window.draw(triangle);
		
		window.draw(ray, 2, sf::Lines);
		window.draw(circleBro);
		window.draw(circleBro2);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};