#include <SFML\Graphics.hpp>
#include "Misc.h"

#pragma once
class Ped : public sf::Sprite
{
public:
	Ped();
	~Ped();

	sf::Vector2f direction;
	sf::Vector2i source;
	float movePedSpeed;

	sf::Clock clockMovement;
};