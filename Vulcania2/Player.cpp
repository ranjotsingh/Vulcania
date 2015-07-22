#include "Player.h"
#include "Misc.h"

Player::Player()
{
	name = "Player.";

	if (!pTexture.loadFromFile("images/peds/Player.png")) { std::cout << "*** Error: Game failed to load 'Player' image." << std::endl; }
	setTexture(pTexture);

	setPosition(620, 590);

	moveSpeed = 100.0f;
	movePedSpeed = 0.035f;

	moving = false;
	running = false;
	autoMove = false;
	reachedSpot = true;
	reachingPoint = sf::Vector2f(0.0f, 0.0f);
	enteredDoor = false;
	frozen = false;
	wasFrozen = false;

	source.x = 1;
	source.y = Misc::Direction::Up;
}

Player::~Player()
{
}