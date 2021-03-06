#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Misc.h"
#include "Objective.h"

class Update
{
public:
	Update();
	~Update();

	std::string saveFileName;
	bool saveExists;

	void load(Player &player, Objective &objective, Misc &misc);
	void save(Player &player, Objective &objective, Misc &misc);
};