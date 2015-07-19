#include "Player.h"

Player::Player()
{
	moving = false;
	running = false;
	enteredDoor = false;
	frozen = false;
	wasFrozen = false;

	source.x = 1;
	source.y = Misc::Direction::Up;
}

Player::~Player()
{
}