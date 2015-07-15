
#include "Menu.h"

Menu::Menu()
{
	Option = optionStartGame;

	menuNewGame = "New Game";
	menuContinueGame = "Continue Game";
	menuOptions = "Options";
	menuQuit = "Quit";
	menuVersion = "Version: 0.1.1";
}


Menu::~Menu()
{
}

void Menu::draw()
{
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "Error: Game failed to load 'noodle' font." << std::endl; }

	textNewGame.setString(menuNewGame);
	textNewGame.setFont(fontNoodle);
	textNewGame.setCharacterSize(40);
	textNewGame.setColor(sf::Color(255, 255, 255));
	textNewGame.setPosition(343, 210);

	textContinueGame.setString(menuContinueGame);
	textContinueGame.setFont(fontNoodle);
	textContinueGame.setCharacterSize(40);
	textContinueGame.setColor(sf::Color(255, 255, 255));
	textContinueGame.setPosition(313.5, 210);

	textOptions.setString(menuOptions);
	textOptions.setFont(fontNoodle);
	textOptions.setCharacterSize(40);
	textOptions.setColor(sf::Color(255, 255, 255));
	textOptions.setPosition(353.5, 260);

	textQuit.setString(menuQuit);
	textQuit.setFont(fontNoodle);
	textQuit.setCharacterSize(40);
	textQuit.setColor(sf::Color(255, 255, 255));
	textQuit.setPosition(374.5, 310);

	textMenuVersion.setString(menuVersion);
	textMenuVersion.setFont(fontNoodle);
	textMenuVersion.setCharacterSize(20);
	textMenuVersion.setColor(sf::Color(255, 255, 255));
	textMenuVersion.setPosition(5, 575);
}

void Menu::navigate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (Option == optionOptions)
		{
			textNewGame.setColor(sf::Color(204, 204, 0));
			textOptions.setColor(sf::Color(255, 255, 255));
			Option = optionStartGame;
		}
		else if (Option == optionQuit)
		{
			textQuit.setColor(sf::Color(255, 255, 255));
			textOptions.setColor(sf::Color(204, 204, 0));
			Option = optionOptions;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (Option == optionStartGame)
		{
			textNewGame.setColor(sf::Color(255, 255, 255));
			textOptions.setColor(sf::Color(204, 204, 0));
			Option = optionOptions;
		}
		else if (Option == optionOptions)
		{
			textOptions.setColor(sf::Color(255, 255, 255));
			textQuit.setColor(sf::Color(204, 204, 0));
			Option = optionQuit;
		}
	}
}