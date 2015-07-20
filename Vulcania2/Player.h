#include <SFML/Graphics.hpp>
#include <iostream>
#include "Misc.h"

#pragma once
class Player : public sf::Sprite
{
public:
	Player();
	~Player();

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
private:
};