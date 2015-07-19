#include "Objective.h"
#include "Player.h"
#include "Misc.h"
#include "Ped.h"

extern Player player;
extern Misc misc;
extern Ped courier;

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
					courier.pedSource = 0;
				}
			}
			else if (part == 1)
			{
				misc.source.y = Misc::Direction::Right;
				player.frozen = true;
				misc.showArrow = false;
				misc.arrowFlash = false;
				misc.showExclaim = true;
				if (courier.getPosition().x >= player.getPosition().x + 26)
				{
					courier.setTextureRect(sf::IntRect((int)courier.pedSource * 32, (int)Misc::Direction::Left * 32, 32, 32));
					courier.move(courier.movePedSpeed * courier.direction * courier.clockMovement.getElapsedTime().asSeconds());
					courier.pedSource++;
					if (courier.pedSource * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						courier.pedSource = 0;
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