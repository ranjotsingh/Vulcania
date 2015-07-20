#include "Objects.h"
#include "Player.h"

extern Player player;
extern Misc misc;

Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::load(sf::Texture& objectsTexture, sf::Sprite& object)
{
	object.setTexture(objectsTexture);
}

void Objects::solid(std::string objectName, float left, float right, float top, float bottom)
{
	if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
		player.setPosition(player.prevPos.x, player.prevPos.y);
}

void Objects::draw(std::string objectName, sf::Texture& objectsTexture, sf::Sprite& objects, int objectNumber, float objectX, float objectY, bool perm)
{
	if (objectNumber == 0)
	{
		objects.setTextureRect(sf::IntRect(0, 0, 57, 78));
	}
	else if (objectNumber == 1)
	{
		objects.setTextureRect(sf::IntRect(63, 0, 115, 156));
	}
	else if (objectNumber == 2)
	{
		objects.setTextureRect(sf::IntRect(185, 0, 64, 110));
	}
	else if (objectNumber == 3)
	{
		objects.setTextureRect(sf::IntRect(0, 87, 42, 46));
	}
	else if (objectNumber == 4)
	{
		objects.setTextureRect(sf::IntRect(0, 156, 305, 33));
	}
	if (perm)
	{
		objects.setPosition(objectX, objectY);
		if (misc.wallHack == false)
		{
			float left = objects.getGlobalBounds().left - 24;
			float right = left + objects.getGlobalBounds().width + 16;
			float top = objects.getGlobalBounds().top - 32;
			float bottom = top + objects.getGlobalBounds().height;
			if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
				player.setPosition(player.prevPos.x, player.prevPos.y);
		}
	}
	else
		std::cout << "*** Error: '" << objectName << "' has failed to load. (invalid object number)." << std::endl;
}