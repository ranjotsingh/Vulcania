#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Misc
{
public:
	Misc();
	~Misc();

	sf::String version;

	sf::Vector2f screenDimensions;

	int gamestate;
	enum GameState { StartMenu, MainMenu, InGame };

	enum Direction { Down, Left, Right, Up };
	sf::Vector2i source;

	bool lockMode;
	bool fastMode;

	bool showObjectiveBox;
	bool showSignBox;

	sf::Sprite textbox;
	std::string textInTextBox;
	sf::Text drawInTextBox;
	bool showTextBox;

	void loadTextBox();

	void loadFloor(sf::Texture& floorsTexture, sf::Sprite& floors);
	void drawFloor(std::string floorName, sf::Texture& floorsTexture, sf::Sprite& floors, int floorNumber, float floorX, float floorY, int floorW, int floorH);

	void loadBoundaryV(sf::Texture& boundaryVTexture, sf::Sprite& boundaryV);
	void drawBoundaryV(std::string boundaryVName, sf::Texture& boundaryVTexture, sf::Sprite& boundaryV, float boundaryX, float boundaryY);
	void loadBoundaryH(sf::Texture& boundaryHTexture, sf::Sprite& boundaryH);
	void drawBoundaryH(std::string boundaryHName, sf::Texture& boundaryHTexture, sf::Sprite& boundaryH, float boundaryX, float boundaryY);
};