#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Misc.h"

class Buildings
{
public:
	Buildings();
	~Buildings();

	void load(sf::Texture& buildingsTexture, sf::Sprite& buildings);
	void draw(Misc &misc, Player &player, std::string buildingName, sf::Texture& buildingsTexture, sf::Sprite& buildings, int buildingNumber, float objectX, float objectY);
	void door(Misc &misc, Player &player, std::string doorName, float doorX, float doorY);
	void spawnDoors(Misc &misc, Player &player);
};