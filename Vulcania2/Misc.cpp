#include <SFML/Graphics.hpp>
#include <iostream>
#include "Misc.h"

extern sf::Vector2f screenDimensions;

Misc::Misc()
{
	gamestate = StartMenu;

	lockMode = true;
	fastMode = false;

	textInTextBox = "";
	showTextBox = false;
}

Misc::~Misc()
{
}

void Misc::loadTextBox()
{
	textbox.setTextureRect(sf::IntRect(200, 0, 500, 146));
	textbox.setPosition((screenDimensions.x - textbox.getGlobalBounds().width) / 2, 444);

	drawInTextBox.setString(textInTextBox);
	drawInTextBox.setCharacterSize(34);
	drawInTextBox.setScale(0.35, 0.35);
	drawInTextBox.setColor(sf::Color(255, 255, 255));
	drawInTextBox.setPosition((textbox.getLocalBounds().width - drawInTextBox.getLocalBounds().width) / 2 + textbox.getPosition().x, (textbox.getLocalBounds().height - 2 * drawInTextBox.getLocalBounds().height) / 2 + textbox.getPosition().y);
}