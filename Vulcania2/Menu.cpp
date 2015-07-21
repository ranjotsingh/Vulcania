#include "Menu.h"

Menu::Menu()
{
	Option = optionStartGame;

	menuNewGame = "New Game";
	menuContinueGame = "Continue Game";
	menuOptions = "Options";
	menuQuit = "Quit";
	menuVersion = "Version: ";
}

Menu::~Menu()
{
}

void Menu::draw(Misc &misc)
{
	textNewGame.setString(menuNewGame);
	textNewGame.setCharacterSize(40);
	textNewGame.setColor(sf::Color(255, 255, 255));
	textNewGame.setPosition((misc.screenDimensions.x - textNewGame.getGlobalBounds().width) / 2, ((misc.screenDimensions.y - textNewGame.getGlobalBounds().height) / 2) - textNewGame.getGlobalBounds().height - 15);
	misc.smooth(textNewGame);

	textContinueGame.setString(menuContinueGame);
	textContinueGame.setCharacterSize(40);
	textContinueGame.setColor(sf::Color(255, 255, 255));
	textContinueGame.setPosition((misc.screenDimensions.x - textContinueGame.getGlobalBounds().width) / 2, ((misc.screenDimensions.y - textContinueGame.getGlobalBounds().height) / 2) - textContinueGame.getGlobalBounds().height - 15);
	misc.smooth(textContinueGame);

	textOptions.setString(menuOptions);
	textOptions.setCharacterSize(40);
	textOptions.setColor(sf::Color(255, 255, 255));
	textOptions.setPosition((misc.screenDimensions.x - textOptions.getGlobalBounds().width) / 2, (misc.screenDimensions.y - textOptions.getGlobalBounds().height) / 2);
	misc.smooth(textOptions);

	textQuit.setString(menuQuit);
	textQuit.setCharacterSize(40);
	textQuit.setColor(sf::Color(255, 255, 255));
	textQuit.setPosition((misc.screenDimensions.x - textQuit.getGlobalBounds().width) / 2, ((misc.screenDimensions.y - textQuit.getGlobalBounds().height) / 2) + textQuit.getGlobalBounds().height + 15);
	misc.smooth(textQuit);

	menuVersion = "Version: " + misc.version;
	textMenuVersion.setString(menuVersion);
	textMenuVersion.setCharacterSize(20);
	textMenuVersion.setColor(sf::Color(255, 255, 255));
	textMenuVersion.setPosition(5, misc.screenDimensions.y - 25);
	misc.smooth(textMenuVersion);
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