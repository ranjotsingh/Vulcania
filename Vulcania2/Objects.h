#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Objects
{
public:
	Objects();
	~Objects();

	void load(sf::Texture& objectsTexture, sf::Sprite& object);
	void solid(std::string objectName, float left, float right, float top, float bottom);
	void draw(std::string objectName, sf::Texture& objectsTexture, sf::Sprite& objects, int objectNumber, float objectX, float objectY);
};