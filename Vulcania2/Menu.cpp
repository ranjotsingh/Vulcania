#include "Menu.h"
#include "Misc.h"

extern Misc misc;

Menu::Menu()
{
	Option = optionStartGame;

	menuNewGame = "New Game";
	menuContinueGame = "Continue Game";
	menuOptions = "Options";
	menuQuit = "Quit";
	menuVersion = "Version: " + misc.version;
}


Menu::~Menu()
{
}

void Menu::draw()
{
	textNewGame.setString(menuNewGame);
	textNewGame.setCharacterSize(40);
	textNewGame.setColor(sf::Color(255, 255, 255));
	textNewGame.setPosition(343, 210);

	textContinueGame.setString(menuContinueGame);
	textContinueGame.setCharacterSize(40);
	textContinueGame.setColor(sf::Color(255, 255, 255));
	textContinueGame.setPosition(313.5, 210);

	textOptions.setString(menuOptions);
	textOptions.setCharacterSize(40);
	textOptions.setColor(sf::Color(255, 255, 255));
	textOptions.setPosition(353.5, 260);

	textQuit.setString(menuQuit);
	textQuit.setCharacterSize(40);
	textQuit.setColor(sf::Color(255, 255, 255));
	textQuit.setPosition(374.5, 310);

	textMenuVersion.setString(menuVersion);
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
			textContinueGame.setColor(sf::Color(204, 204, 0));
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
			textContinueGame.setColor(sf::Color(255, 255, 255));
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