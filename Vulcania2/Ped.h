#pragma once
#include <SFML\Graphics.hpp>
#include "Misc.h"

class Ped : public sf::Sprite
{
public:
	Ped();
	~Ped();

	sf::Vector2f direction;
	sf::Vector2i source;
	float movePedSpeed;
	bool reachedSpot;
	sf::Vector2f reachingPoint;

	sf::Clock clockMovement;
};