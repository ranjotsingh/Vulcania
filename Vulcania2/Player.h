#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Sprite
{
public:
	Player();
	~Player();

	std::string name;

	sf::Vector2f prevPos;
	sf::Vector2f direction;
	float moveSpeed;
	float movePedSpeed;
	sf::Clock clockMovement;

	bool moving;
	bool running;
	bool autoMove;
	bool reachedSpot;
	sf::Vector2f reachingPoint;
	bool enteredDoor;
	bool frozen;
	bool wasFrozen;

	sf::Vector2i source;
};