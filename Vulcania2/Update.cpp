#include "Update.h"

Update::Update()
{
	saveFileName = "save/save001.sav";
	saveExists = false;
}

Update::~Update()
{
}

void Update::load(Player &player, Objective &objective, Misc &misc)
{
	std::ifstream saveFile(saveFileName);
	if (saveFile.is_open())
	{
		float x, y;
		while (saveFile
			>> player.name
			>> player.source.y
			>> x
			>> y
			>> player.frozen
			>> player.autoMove
			>> misc.autoMode
			>> objective.currentObj
			>> objective.part
			>> objective.subPart
		);
		player.setPosition(x, y);
		misc.textPlayerName.setString(player.name);
		misc.textPlayerName.setPosition(misc.screenDimensions.x - misc.textPlayerName.getGlobalBounds().width - 5, misc.textPlayerName.getPosition().y);
		/*
		std::cout << player.name << std::endl;
		std::cout << player.source.y << std::endl;
		std::cout << player.getPosition().x << std::endl;
		std::cout << player.getPosition().y << std::endl;
		std::cout << player.frozen << std::endl;
		std::cout << player.autoMove << std::endl;
		std::cout << misc.autoMode << std::endl;
		std::cout << objective.currentObj << std::endl;
		std::cout << objective.part << std::endl;
		std::cout << objective.subPart << std::endl;
		*/
	}
	else
		std::cout << "*** Game did not find a saved game file." << std::endl;
	saveFile.close();
}

void Update::save(Player &player, Objective &objective, Misc &misc)
{
	if (!player.autoMove && !misc.autoMode)
	{
		std::ofstream saveFile(saveFileName);
		saveFile << player.name << std::endl;								// 1
		saveFile << player.source.y << std::endl;							// 2
		saveFile << (int)player.getPosition().x << std::endl;				// 3
		saveFile << (int)player.getPosition().y << std::endl;				// 4
		saveFile << player.frozen << std::endl;								// 5
		saveFile << player.autoMove << std::endl;							// 6
		saveFile << misc.autoMode << std::endl;								// 7
		saveFile << objective.currentObj << std::endl;						// 8
		saveFile << objective.part << std::endl;							// 9
		saveFile << objective.subPart << std::endl;							// 10
		std::cout << "*** Game has saved information into the game save file." << std::endl;
		saveFile.close();
	}
	else
		std::cout << "*** Game cannot save at this time." << std::endl;
}