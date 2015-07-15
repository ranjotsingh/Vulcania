#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
class Menu
{
public:
	Menu();
	~Menu();

	enum Options { optionStartGame, optionOptions, optionQuit };
	int Option;

	void draw();
	void navigate();

	sf::String menuNewGame;
	sf::String menuContinueGame;
	sf::String menuOptions;
	sf::String menuQuit;
	sf::String menuVersion;

	sf::Text textNewGame;
	sf::Text textContinueGame;
	sf::Text textOptions;
	sf::Text textQuit;
	sf::Text textMenuVersion;
};