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
		int i = 0;
		std::string str;
		while (getline(saveFile, str))
		{
			if (i == 0) { player.name = str; }
			else if (i == 1) { player.source.y = std::stoi(str); }
			else if (i == 2) { player.setPosition(std::stof(str), player.getPosition().y); }
			else if (i == 3) { player.setPosition(player.getPosition().x, std::stof(str)); }
			else if (i == 4) { player.frozen = misc.to_bool(str); }
			else if (i == 5) { player.autoMove = misc.to_bool(str); }
			else if (i == 6) { misc.autoMode = misc.to_bool(str); }
			else if (i == 7) { objective.currentObj = std::stoi(str); }
			else if (i == 8) { objective.part = std::stoi(str); }
			else if (i == 9) { objective.subPart = std::stoi(str); }
			++i;
		}
		misc.textPlayerName.setString(player.name);
		misc.textPlayerName_Outline1.setString(player.name);
		misc.textPlayerName_Outline2.setString(player.name);
		misc.textPlayerName_Outline3.setString(player.name);
		misc.textPlayerName_Outline4.setString(player.name);
		misc.textPlayerName.setPosition(misc.screenDimensions.x - misc.textPlayerName.getGlobalBounds().width - 5, misc.textPlayerName.getPosition().y);
		misc.textPlayerName_Outline1.setPosition(misc.textPlayerName.getPosition().x - 1, misc.textPlayerName.getPosition().y);
		misc.textPlayerName_Outline2.setPosition(misc.textPlayerName.getPosition().x + 1, misc.textPlayerName.getPosition().y);
		misc.textPlayerName_Outline3.setPosition(misc.textPlayerName.getPosition().x, misc.textPlayerName.getPosition().y - 1);
		misc.textPlayerName_Outline4.setPosition(misc.textPlayerName.getPosition().x, misc.textPlayerName.getPosition().y + 1);
		misc.smooth(misc.textPlayerName);
		misc.smooth(misc.textPlayerName_Outline1);
		misc.smooth(misc.textPlayerName_Outline2);
		misc.smooth(misc.textPlayerName_Outline3);
		misc.smooth(misc.textPlayerName_Outline4);
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