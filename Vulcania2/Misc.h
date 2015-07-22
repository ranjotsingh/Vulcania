#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Misc
{
public:
	Misc();
	~Misc();

	std::string gameName;
	sf::String version;
	sf::Vector2f screenDimensions;

	sf::Image icon;

	sf::Texture boxesTexture;

	int gamestate;
	enum GameState { StartMenu, MainMenu, InGame };

	enum Direction { Down, Left, Right, Up };

	bool lockMode;
	bool wallHack;

	bool autoMode;

	bool paused;

	bool typing;

	bool showObjectiveBox;
	bool showSignBox;

	bool arrowFlash;
	bool showArrow;
	bool showExclaim;

	sf::Text textPlayerName;

	void smooth(sf::Text &text);
	sf::Sprite textbox;
	std::string textInTextBox;
	sf::Text drawInTextBox;
	sf::Text drawInTextBox_Outline1;
	sf::Text drawInTextBox_Outline2;
	sf::Text drawInTextBox_Outline3;
	sf::Text drawInTextBox_Outline4;
	bool showTextBox;

	void loadTextBox();

	void loadBackground(sf::Texture& backgroundsTexture, sf::Sprite& backgrounds);
	void drawBackground(std::string backgroundName, sf::Texture& backgroundsTexture, sf::Sprite& backgrounds, int backgroundNumber, float backgroundX, float backgroundY, float backgroundW, float backgroundH);

	void loadFloor(sf::Texture& floorsTexture, sf::Sprite& floors);
	void drawFloor(std::string floorName, sf::Texture& floorsTexture, sf::Sprite& floors, int floorNumber, float floorX, float floorY, int floorW, int floorH);

	void loadBoundaryV(sf::Texture& boundaryVTexture, sf::Sprite& boundaryV);
	void drawBoundaryV(Player &player, std::string boundaryVName, sf::Texture& boundaryVTexture, sf::Sprite& boundaryV, float boundaryX, float boundaryY);
	void loadBoundaryH(sf::Texture& boundaryHTexture, sf::Sprite& boundaryH);
	void drawBoundaryH(Player &player, std::string boundaryHName, sf::Texture& boundaryHTexture, sf::Sprite& boundaryH, float boundaryX, float boundaryY);

	sf::Font fontMain;
	sf::Font fontNoodle;
	sf::Font fontDaniel;
};