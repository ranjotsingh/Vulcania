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
	bool moving;
	bool running;
	bool enteredDoor;
	bool frozen;
	bool wasFrozen;

	sf::Vector2i source;
private:
};