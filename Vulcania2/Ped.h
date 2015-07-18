#include <SFML\Graphics.hpp>

#pragma once
class Ped : public sf::Sprite
{
public:
	Ped();
	~Ped();

	sf::Vector2f direction;
	float pedSource;
	float movePedSpeed;

	sf::Clock clockMovement;
};