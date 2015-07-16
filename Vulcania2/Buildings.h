#include <SFML\Graphics.hpp>
#include <iostream>

#pragma once
class Buildings
{
public:
	Buildings();
	~Buildings();

	void load(sf::Texture& buildingsTexture, sf::Sprite& buildings);
	void draw(std::string buildingName, sf::Texture& buildingsTexture, sf::Sprite& buildings, int buildingNumber, float objectX, float objectY);
	void door(std::string doorName, float doorX, float doorY);
	void spawnDoors();
};