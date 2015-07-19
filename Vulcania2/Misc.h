#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Misc
{
public:
	Misc();
	~Misc();

	std::string gameName;
	sf::String version;
	sf::Vector2f screenDimensions;

	int gamestate;
	enum GameState { StartMenu, MainMenu, InGame };

	enum Direction { Down, Left, Right, Up };

	bool lockMode;
	bool wallHack;

	bool paused;

	bool showObjectiveBox;
	bool showSignBox;

	bool arrowFlash;
	bool showArrow;
	bool showExclaim;

	sf::Sprite textbox;
	std::string textInTextBox;
	sf::Text drawInTextBox;
	bool showTextBox;

	void loadTextBox();

	void loadBackground(sf::Texture& backgroundsTexture, sf::Sprite& backgrounds);
	void drawBackground(std::string backgroundName, sf::Texture& backgroundsTexture, sf::Sprite& backgrounds, int backgroundNumber, float backgroundX, float backgroundY, float backgroundW, float backgroundH);

	void loadFloor(sf::Texture& floorsTexture, sf::Sprite& floors);
	void drawFloor(std::string floorName, sf::Texture& floorsTexture, sf::Sprite& floors, int floorNumber, float floorX, float floorY, int floorW, int floorH);

	void loadBoundaryV(sf::Texture& boundaryVTexture, sf::Sprite& boundaryV);
	void drawBoundaryV(std::string boundaryVName, sf::Texture& boundaryVTexture, sf::Sprite& boundaryV, float boundaryX, float boundaryY);
	void loadBoundaryH(sf::Texture& boundaryHTexture, sf::Sprite& boundaryH);
	void drawBoundaryH(std::string boundaryHName, sf::Texture& boundaryHTexture, sf::Sprite& boundaryH, float boundaryX, float boundaryY);
};