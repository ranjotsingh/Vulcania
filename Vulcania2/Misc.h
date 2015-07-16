#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Misc
{
public:
	Misc();
	~Misc();

	int gamestate;
	enum GameState { StartMenu, MainMenu, InGame };

	enum Direction { Down, Left, Right, Up };

	bool lockMode;
	bool fastMode;

	sf::Sprite textbox;
	std::string textInTextBox;
	sf::Text drawInTextBox;
	bool showTextBox;

	void loadTextBox();
};