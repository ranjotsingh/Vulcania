#include "Ped.h"

Ped::Ped()
{
	movePedSpeed = 0.35f;
	source.x = 1;
	source.y = Misc::Direction::Down;

	reachedSpot = true;
	reachingPoint = sf::Vector2f(0.0f, 0.0f);
}

Ped::~Ped()
{
}