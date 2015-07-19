#include "Buildings.h"
#include "Player.h"
#include "Misc.h"

extern Player player;
extern Misc misc;
extern sf::Vector2i source;

Buildings::Buildings()
{
}

Buildings::~Buildings()
{
}

void Buildings::spawnDoors()
{
	door("Main House", 827, 510);
	door("House 0", 960, 514);
	door("House 1", 1082, 516);
	door("House 2", 793, 670);
	door("House 3", 895, 669);
	door("House 4", 1072, 670);
}

void Buildings::load(sf::Texture& buildingsTexture, sf::Sprite& buildings)
{
	buildings.setTexture(buildingsTexture);
}

void Buildings::draw(std::string buildingName, sf::Texture& buildingsTexture, sf::Sprite& buildings, int buildingNumber, float objectX, float objectY)
{
	if (buildingNumber == 0)
	{
		buildings.setTextureRect(sf::IntRect(0, 0, 140, 122));
	}
	else if (buildingNumber == 1)
	{
		buildings.setTextureRect(sf::IntRect(158, 0, 116, 114));
	}
	else if (buildingNumber == 2)
	{
		buildings.setTextureRect(sf::IntRect(298, 0, 80, 97));
	}
	else if (buildingNumber == 3)
	{
		buildings.setTextureRect(sf::IntRect(401, 0, 61, 65));
	}
	else if (buildingNumber == 4)
	{
		buildings.setTextureRect(sf::IntRect(482, 0, 108, 93));
	}
	else if (buildingNumber == 5)
	{
		buildings.setTextureRect(sf::IntRect(612, 0, 124, 98));
	}
	if (buildingNumber >= 0 && buildingNumber <= 5)
	{
		buildings.setPosition(objectX, objectY);
		if (misc.wallHack == false)
		{
			float left = buildings.getGlobalBounds().left - 24;
			float right = left + buildings.getGlobalBounds().width + 16;
			float top = buildings.getGlobalBounds().top - 32;
			float bottom = top + buildings.getGlobalBounds().height;
			if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
				player.setPosition(player.prevPos.x, player.prevPos.y);
		}
	}
	else
		std::cout << "*** Error: '" << buildingName << "' has failed to load. (invalid building number)." << std::endl;
}

void Buildings::door(std::string doorName, float doorX, float doorY)
{
	sf::Vector2f newDoor(doorX, doorY);
	float doorRadius = 10;
	if (player.getPosition().x >= doorX - doorRadius && player.getPosition().x <= doorX + doorRadius && player.getPosition().y >= doorY - 1 && player.getPosition().y <= doorY + 2)
	{
		if (misc.gamestate == Misc::GameState::InGame && player.moving == true && player.source.y == Misc::Direction::Up && player.enteredDoor == false)
		{
			if (misc.lockMode == false)
			{
				std::cout << "*** Player has entered '" + doorName + "' door." << std::endl;
				player.enteredDoor = true;
			}
			else if (misc.lockMode == true)
			{
				std::cout << "*** Player has tried to enter '" + doorName + "' door. (lockMode)" << std::endl;
				misc.showTextBox = true;
				player.frozen = true;
				misc.textInTextBox = "Perhaps I should complete the task at hand first.";
			}
		}
	}
}