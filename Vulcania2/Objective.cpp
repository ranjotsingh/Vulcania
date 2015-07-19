#include "Objective.h"
#include "Player.h"
#include "Misc.h"
#include "Ped.h"

extern Player player;
extern Misc misc;
extern Ped courier;
extern Ped lucius;
extern Ped shadow;
extern Ped tobias;

Objective::Objective()
{
	currentObj = 0;
	part = 0;
	subPart = 0;
	objCurrentText = "None";
}

Objective::~Objective()
{
}

void Objective::initiate()
{
	if (misc.gamestate == Misc::GameState::InGame && misc.paused == false)
	{
		if (currentObj == 0)
		{
			objCurrentText = "Walk with Tobias.";
			shadow.setTextureRect(sf::IntRect((int)shadow.source.x * 32, (int)shadow.source.y * 32, 32, 32));
			shadow.source.y = Misc::Direction::Down;
			lucius.setTextureRect(sf::IntRect((int)lucius.source.x * 32, (int)lucius.source.y * 32, 32, 32));
			lucius.source.y = Misc::Direction::Left;
			tobias.setTextureRect(sf::IntRect((int)tobias.source.x * 32, (int)tobias.source.y * 32, 32, 32));
			tobias.source.y = Misc::Direction::Left;
		}
		else if (currentObj == 5)
		{
			if (part == 0)
			{
				objCurrentText = "Go home.";
				if (player.getPosition().x >= 820 && player.getPosition().x <= 851 && player.getPosition().y >= 510 && player.getPosition().y <= 538)
				{
					part = 1;
					courier.setPosition(1114, player.getPosition().y);
					courier.direction = player.getPosition() - courier.getPosition();
					courier.source.x = 1;
				}
			}
			else if (part == 1)
			{
				player.source.y = Misc::Direction::Right;
				player.frozen = true;
				misc.showArrow = false;
				misc.arrowFlash = false;
				misc.showExclaim = true;
				if (courier.getPosition().x >= player.getPosition().x + 26)
				{
					courier.setTextureRect(sf::IntRect((int)courier.source.x * 32, (int)Misc::Direction::Left * 32, 32, 32));
					courier.move(courier.movePedSpeed * courier.direction * courier.clockMovement.getElapsedTime().asSeconds());
					courier.source.x++;
					if (courier.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						courier.source.x = 0;
				}
				else
				{
					misc.showExclaim = false;
					misc.showTextBox = true;
					part = 2;
					subPart = 0;
				}
			}
			else if (part == 2)
			{
				player.frozen = true;
				courier.source.x = 1;
				if (subPart == 0)
				{
					misc.textInTextBox = "MAILMAN: Do you live here? I have a package for this address.";
					misc.showTextBox = true;
				}
				else if (subPart == 1)
				{
					misc.textInTextBox = "MAILMAN hands you the package.";
					misc.showTextBox = true;
				}
				else if (subPart == 2)
				{
					misc.textInTextBox = "MAILMAN: Sign here with your name.";
					misc.showTextBox = true;
				}
				else if (subPart == 3)
				{
					objCurrentText = "Sign with your name.";
					misc.showSignBox = true;
					misc.showTextBox = false;
				}
			}
		}
		else
		{
			objCurrentText = "None.";
		}
	}
}