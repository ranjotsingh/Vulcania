#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
	if (!Building.loadFromFile("images/map/buildings.png")) { std::cout << "*** Error: Game failed to load 'buildings' image." << std::endl; }
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::spawnDoors(Misc &misc, Player &player)
{
	door(misc, player, "Main House", 827, 510);
	door(misc, player, "House 0", 960, 514);
	door(misc, player, "House 1", 1082, 516);
	door(misc, player, "House 2", 793, 670);
	door(misc, player, "House 3", 895, 669);
	door(misc, player, "House 4", 1072, 670);
}

void BuildingManager::load(sf::Texture& buildingsTexture, sf::Sprite& buildings)
{
	buildings.setTexture(buildingsTexture);
}

void BuildingManager::draw(Misc &misc, Player &player, std::string buildingName, sf::Texture& buildingsTexture, sf::Sprite& buildings, int buildingNumber, float objectX, float objectY)
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

void BuildingManager::door(Misc &misc, Player &player, std::string doorName, float doorX, float doorY)
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