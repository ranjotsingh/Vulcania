#include "Misc.h"

Misc::Misc()
{
	gameName = "Vulcania: Commencement";
	version = "0.1.1";
	screenDimensions.x = 1024;
	screenDimensions.y = 768;

	gamestate = StartMenu;

	lockMode = true;
	wallHack = false;

	paused = false;

	typing = false;

	showObjectiveBox = true;
	showSignBox = false;

	arrowFlash = false;
	showArrow = false;
	showExclaim = false;

	textInTextBox = "";
	showTextBox = false;

	if (!fontMain.loadFromFile("fonts/tahoma.ttf")) { std::cout << "*** Error: Game failed to load 'tahoma' font." << std::endl; }
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "*** Error: Game failed to load 'noodle' font." << std::endl; }
	if (!fontDaniel.loadFromFile("fonts/Daniel-Black.otf")) { std::cout << "*** Error: Game failed to load 'Daniel-Black' font." << std::endl; }
}

Misc::~Misc()
{
}

void Misc::smooth(sf::Text &text)
{
	text.setPosition((float)std::round(text.getPosition().x), (float)std::round(text.getPosition().y));
}

void Misc::loadTextBox()
{	
	textbox.setTextureRect(sf::IntRect(200, 0, 500, 146));
	textbox.setPosition((screenDimensions.x - textbox.getGlobalBounds().width) / 2, screenDimensions.y - 30);

	drawInTextBox.setString(textInTextBox);
	drawInTextBox.setCharacterSize(18);
	drawInTextBox.setColor(sf::Color(255, 255, 255));
	drawInTextBox.setPosition((textbox.getGlobalBounds().width - drawInTextBox.getGlobalBounds().width) / 2 + textbox.getPosition().x, screenDimensions.y - 30);
	smooth(drawInTextBox);
	drawInTextBox_Outline1.setString(textInTextBox);
	drawInTextBox_Outline1.setCharacterSize(drawInTextBox.getCharacterSize());
	drawInTextBox_Outline1.setColor(sf::Color(0, 0, 0));
	drawInTextBox_Outline1.setPosition(drawInTextBox.getPosition());
	smooth(drawInTextBox_Outline1);
	drawInTextBox_Outline2.setString(textInTextBox);
	drawInTextBox_Outline2.setCharacterSize(drawInTextBox.getCharacterSize());
	drawInTextBox_Outline2.setColor(sf::Color(0, 0, 0));
	drawInTextBox_Outline2.setPosition(drawInTextBox.getPosition());
	smooth(drawInTextBox_Outline2);
	drawInTextBox_Outline3.setString(textInTextBox);
	drawInTextBox_Outline3.setCharacterSize(drawInTextBox.getCharacterSize());
	drawInTextBox_Outline3.setColor(sf::Color(0, 0, 0));
	drawInTextBox_Outline3.setPosition(drawInTextBox.getPosition());
	smooth(drawInTextBox_Outline3);
	drawInTextBox_Outline4.setString(textInTextBox);
	drawInTextBox_Outline4.setCharacterSize(drawInTextBox.getCharacterSize());
	drawInTextBox_Outline4.setColor(sf::Color(0, 0, 0));
	drawInTextBox_Outline4.setPosition(drawInTextBox.getPosition());
	smooth(drawInTextBox_Outline4);
}

void Misc::loadBackground(sf::Texture& backgroundsTexture, sf::Sprite& backgrounds)
{
	backgroundsTexture.setRepeated(true);
	backgrounds.setTextureRect(sf::IntRect(0, 0, 1, 1));
	backgrounds.setTexture(backgroundsTexture);
}

void Misc::drawBackground(std::string backgroundName, sf::Texture& backgroundsTexture, sf::Sprite& backgrounds, int backgroundNumber, float backgroundX, float backgroundY, float backgroundW, float backgroundH)
{
	if (backgroundNumber == 0)
	{
		backgrounds.setTextureRect(sf::IntRect(0, 0, (int)backgroundW, (int)backgroundH));
		backgrounds.setPosition(backgroundX, backgroundY);
	}
	else
	{
		std::cout << "*** Background: '" << backgroundName << "' has failed to load. (invalid background number)." << std::endl;
	}
}

void Misc::loadFloor(sf::Texture& floorsTexture, sf::Sprite& floors)
{
	floorsTexture.setRepeated(true);
	floors.setTextureRect(sf::IntRect(0, 0, 64, 64));
	floors.setTexture(floorsTexture);
}

void Misc::drawFloor(std::string floorName, sf::Texture& floorsTexture, sf::Sprite& floors, int floorNumber, float floorX, float floorY, int floorW, int floorH)
{
	if (floorNumber == 0)
	{
		floors.setTextureRect(sf::IntRect(0, 0, floorW, floorH));
		floors.setPosition(floorX, floorY);
	}
	else
	{
		std::cout << "*** Floor: '" << floorName << "' has failed to load. (invalid floor number)." << std::endl;
	}
}

void Misc::loadBoundaryV(sf::Texture& boundaryVTexture, sf::Sprite& boundaryV)
{
	if (!boundaryVTexture.loadFromFile("images/map/treeboundvert.png")) { std::cout << "*** Error: Game failed to load 'treeboundvert' image." << std::endl; }
	boundaryV.setTexture(boundaryVTexture);
}

void Misc::drawBoundaryV(Player &player, std::string boundaryVName, sf::Texture& boundaryVTexture, sf::Sprite& boundaryV, float boundaryX, float boundaryY)
{
	boundaryV.setPosition(boundaryX, boundaryY);
	if (wallHack == false)
	{
		float left = boundaryV.getGlobalBounds().left - 24;
		float right = left + boundaryV.getGlobalBounds().width + 16;
		float top = boundaryV.getGlobalBounds().top - 32;
		float bottom = top + boundaryV.getGlobalBounds().height;
		if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
			player.setPosition(player.prevPos.x, player.prevPos.y);
	}
}

void Misc::loadBoundaryH(sf::Texture& boundaryHTexture, sf::Sprite& boundaryH)
{
	if (!boundaryHTexture.loadFromFile("images/map/treeboundhoriz.png")) { std::cout << "*** Error: Game failed to load 'treeboundhoriz' image." << std::endl; }
	boundaryH.setTexture(boundaryHTexture);
}

void Misc::drawBoundaryH(Player &player, std::string boundaryHName, sf::Texture& boundaryHTexture, sf::Sprite& boundaryH, float boundaryX, float boundaryY)
{
	boundaryH.setPosition(boundaryX, boundaryY);
	if (wallHack == false)
	{
		float left = boundaryH.getGlobalBounds().left - 24;
		float right = left + boundaryH.getGlobalBounds().width + 16;
		float top = boundaryH.getGlobalBounds().top - 32;
		float bottom = top + boundaryH.getGlobalBounds().height;
		if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
			player.setPosition(player.prevPos.x, player.prevPos.y);
	}
}