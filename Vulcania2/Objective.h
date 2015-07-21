#pragma once
#include <iostream>
#include "Player.h"
#include "Misc.h"
#include "Ped.h"

class Objective
{
public:
	Objective();
	~Objective();

	int currentObj;
	int part;
	int subPart;
	std::string name;
	std::string objCurrentText;

	void initiate(Misc &misc, Player &player, Ped &tobias, Ped &lucius, Ped &courier, Ped &shadow);
};