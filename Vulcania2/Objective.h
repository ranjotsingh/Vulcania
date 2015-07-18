#include <iostream>

#pragma once
class Objective
{
public:
	Objective();
	~Objective();

	int currentObj;
	int part;
	int subPart;
	std::string objCurrentText;

	void initiate();
};