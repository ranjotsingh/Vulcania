#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Misc.h"

class Objects
{
public:
	Objects();
	~Objects();

	void load(sf::Texture& objectsTexture, sf::Sprite& object);
	void solid(Player &player, std::string objectName, float left, float right, float top, float bottom);
	void draw(Misc &misc, Player &player, std::string objectName, sf::Texture& objectsTexture, sf::Sprite& objects, int objectNumber, float objectX, float objectY, bool perm);
};