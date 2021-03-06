#include "Objective.h"

Objective::Objective()
{
	currentObj = 0;
	part = 0;
	subPart = 0;
	name = "None";
	objCurrentText = "None.";
}

Objective::~Objective()
{
}

void Objective::initiate(Misc &misc, Player &player, Ped &tobias, Ped &lucius, Ped &courier, Ped &shadow)
{
	if (misc.gamestate == Misc::GameState::InGame && misc.paused == false)
	{
		if (currentObj == 0)
		{
			name = "Uncle Trent";
			objCurrentText = "Walk with Tobias.";
			player.setPosition(2710, 1055);
			lucius.setPosition(2595, 1068);
			shadow.setPosition(2782, 1775);
			tobias.setPosition(2710, 1088);
			player.source.y = Misc::Direction::Left;
			tobias.source.y = Misc::Direction::Left;
			lucius.source.y = Misc::Direction::Left;
			shadow.source.y = Misc::Direction::Down;
			currentObj = 1;
		}
		else if (currentObj == 1)
		{
			misc.showTextBox = true;
			if (player.getPosition().x > 2401 && player.getPosition().x < 2710 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "TOBIAS: Damn! Are you serious? So, Lucius is four years now?";
			else if (player.getPosition().x > 2072 && player.getPosition().x < 2401 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "YOU: I'd figure. He was just a little pup when we found him.";
			else if (player.getPosition().x > 1838 && player.getPosition().x < 2072 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "TOBIAS: He's already grown too.";
			else if (player.getPosition().x > 1589 && player.getPosition().x < 1838 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "YOU: Meh. I'm sure he'll only get bigger.";
			else if (player.getPosition().x > 1364 && player.getPosition().x < 1589 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "TOBIAS: Shit... Maybe.";
			else if (player.getPosition().x > 1186 && player.getPosition().x < 1364 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "";
			else if (player.getPosition().x > 883 && player.getPosition().x < 1186 && player.getPosition().y > 1054 && player.getPosition().y < 1056)
				misc.textInTextBox = "TOBIAS: Hey. So, what's up with Mila? I haven't seen her in a while.";
			else if (player.getPosition().x > 605 && player.getPosition().x < 883 && player.getPosition().y > 1054 && player.getPosition().y < 1085)
				misc.textInTextBox = "YOU: She's still in Tarad with her family. We'll see her at the wedding though.";
			else if (player.getPosition().x > 605 && player.getPosition().x < 607 && player.getPosition().y > 1085 && player.getPosition().y < 1515)
				misc.textInTextBox = "TOBIAS: Is she? God damn it. You better not abandon me again. I'll\n be bored as hell. I don't even know anyone else there.";
			else if (player.getPosition().x > 605 && player.getPosition().x < 820 && player.getPosition().y > 1515 && player.getPosition().y < 1616)
				misc.textInTextBox = "YOU: Oh, please. There'll be plenty of women running around. Just take your pick.";
			else if (player.getPosition().x > 820 && player.getPosition().x < 1140 && player.getPosition().y > 1612 && player.getPosition().y < 1616)
				misc.textInTextBox = "TOBIAS: Oh, you know damn well I will. But, don't let this Mila chick get into your head.";
			else if (player.getPosition().x > 1140 && player.getPosition().x < 1370 && player.getPosition().y > 1565 && player.getPosition().y < 1840)
				misc.textInTextBox = "YOU: Get into my head? What the fuck are you going on ab-...";
			else if (player.getPosition().x > 1370 && player.getPosition().x < 1500 && player.getPosition().y > 1565 && player.getPosition().y < 1840)
				misc.textInTextBox = "YOU: Wait! Lucius! Wait! ...where the hell is he going?";
			else if (player.getPosition().x > 1500 && player.getPosition().x < 1550 && player.getPosition().y > 1565 && player.getPosition().y < 1840)
				misc.textInTextBox = "TOBIAS: Come on! Let's go after him!";
			else
				misc.textInTextBox = "";

			tobias.setTextureRect(sf::IntRect((int)tobias.source.x * 32, (int)tobias.source.y * 32, 32, 32));
			lucius.setTextureRect(sf::IntRect((int)lucius.source.x * 32, (int)lucius.source.y * 32, 32, 32));
			shadow.setTextureRect(sf::IntRect((int)shadow.source.x * 32, (int)shadow.source.y * 32, 32, 32));
			bool continueLucius = false;

			if (misc.wallHack == false)
			{
				float left = tobias.getGlobalBounds().left - 24;
				float right = left + tobias.getGlobalBounds().width + 16;
				float top = tobias.getGlobalBounds().top - 32;
				float bottom = top + tobias.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}
			if (misc.wallHack == false)
			{
				float left = lucius.getGlobalBounds().left - 24;
				float right = left + lucius.getGlobalBounds().width + 16;
				float top = lucius.getGlobalBounds().top - 32;
				float bottom = top + lucius.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}
			if (misc.wallHack == false)
			{
				float left = shadow.getGlobalBounds().left - 24;
				float right = left + shadow.getGlobalBounds().width + 16;
				float top = shadow.getGlobalBounds().top - 32;
				float bottom = top + shadow.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}

			if (part == 0)
			{
				player.reachingPoint = sf::Vector2f(607, player.getPosition().y);
				tobias.reachingPoint = sf::Vector2f(639, tobias.getPosition().y);
				lucius.reachingPoint = sf::Vector2f(625, lucius.getPosition().y);

				misc.autoMode = true;
				player.autoMove = true;
				player.frozen = true;
				player.direction = player.reachingPoint - player.getPosition();
				player.reachedSpot = false;
				player.source.y = Misc::Direction::Left;
				player.movePedSpeed = 0.035f;
				tobias.direction = tobias.reachingPoint - tobias.getPosition();
				tobias.reachedSpot = false;
				tobias.source.y = Misc::Direction::Left;
				tobias.movePedSpeed = 0.0355f;
				lucius.direction = lucius.reachingPoint - lucius.getPosition();
				lucius.reachedSpot = false;
				lucius.source.y = Misc::Direction::Left;
				lucius.movePedSpeed = 0.03725f;
				continueLucius = false;
				shadow.source.y = Misc::Direction::Down;
				part = 1;
			}
			if (part == 1)
			{
				if (player.getPosition().x >= player.reachingPoint.x)
				{
					player.move(player.movePedSpeed * player.direction * courier.clockMovement.getElapsedTime().asSeconds());
					player.source.x++;
					if (player.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						player.source.x = 0;
				}
				else { player.reachedSpot = true; }
				if (tobias.getPosition().x >= tobias.reachingPoint.x)
				{
					tobias.move(tobias.movePedSpeed * tobias.direction * courier.clockMovement.getElapsedTime().asSeconds());
					tobias.source.x++;
					if (tobias.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						tobias.source.x = 0;
				}
				else { tobias.reachedSpot = true; }
				if (lucius.getPosition().x >= lucius.reachingPoint.x)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
				}
				else { lucius.reachedSpot = true; }
				if (lucius.reachedSpot)
				{
					lucius.reachingPoint = sf::Vector2f(lucius.getPosition().x, 1630);
					lucius.direction = lucius.reachingPoint - lucius.getPosition();
					lucius.reachedSpot = false;
					lucius.source.y = Misc::Direction::Down;
					lucius.movePedSpeed = 0.1f;
					continueLucius = true;
				}
				if (continueLucius)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
				}
				if (player.reachedSpot && tobias.reachedSpot)
				{
					part = 2;
					tobias.source.x = 1;
					player.source.y = Misc::Direction::Down;
					player.reachedSpot = false;
					tobias.reachedSpot = false;
					lucius.reachedSpot = false;
					continueLucius = false;

					player.reachingPoint = sf::Vector2f(player.getPosition().x, 1088);
					player.direction = player.reachingPoint - player.getPosition();
					player.movePedSpeed = 1.5f;
				}
			}
			if (part == 2)
			{
				if (player.getPosition().y <= player.reachingPoint.y)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
					player.move(player.movePedSpeed * player.direction * courier.clockMovement.getElapsedTime().asSeconds());
					player.source.x++;
					if (player.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						player.source.x = 0;
				}
				else
				{
					part = 3;
					tobias.source.y = Misc::Direction::Down;

					player.reachingPoint = sf::Vector2f(player.getPosition().x, 1614);
					player.direction = player.reachingPoint - player.getPosition();
					player.movePedSpeed = 0.1f;
					tobias.reachingPoint = sf::Vector2f(tobias.getPosition().x, 1647);
					tobias.direction = tobias.reachingPoint - tobias.getPosition();
					tobias.movePedSpeed = 0.094f;
				}
			}
			if (part == 3)
			{
				if (player.getPosition().y <= player.reachingPoint.y)
				{
					player.move(player.movePedSpeed * player.direction * courier.clockMovement.getElapsedTime().asSeconds());
					player.source.x++;
					if (player.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						player.source.x = 0;
				}
				else { player.reachedSpot = true; }
				if (tobias.getPosition().y <= tobias.reachingPoint.y)
				{
					tobias.move(tobias.movePedSpeed * tobias.direction * courier.clockMovement.getElapsedTime().asSeconds());
					tobias.source.x++;
					if (tobias.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						tobias.source.x = 0;
				}
				else { tobias.reachedSpot = true; }
				if (lucius.getPosition().y <= lucius.reachingPoint.y)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
				}
				else { lucius.reachedSpot = true; }
				if (lucius.reachedSpot)
				{
					lucius.reachingPoint = sf::Vector2f(1680, lucius.getPosition().y);
					lucius.direction = lucius.reachingPoint - lucius.getPosition();
					lucius.reachedSpot = false;
					lucius.source.y = Misc::Direction::Right;
					lucius.movePedSpeed = 0.05f;
					continueLucius = true;
				}
				if (continueLucius)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
				}
				if (player.reachedSpot && tobias.reachedSpot)
				{
					part = 4;
					tobias.source.x = 1;
					player.source.y = Misc::Direction::Right;
					player.reachedSpot = false;
					tobias.reachedSpot = false;
					lucius.reachedSpot = false;
					continueLucius = false;

					player.reachingPoint = sf::Vector2f(638, player.getPosition().y);
					player.direction = player.reachingPoint - player.getPosition();
					player.movePedSpeed = 1.5f;
				}
			}
			if (part == 4)
			{
				if (player.getPosition().x <= player.reachingPoint.x)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
					player.move(player.movePedSpeed * player.direction * courier.clockMovement.getElapsedTime().asSeconds());
					player.source.x++;
					if (player.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						player.source.x = 0;
				}
				else
				{
					part = 5;
					tobias.source.y = Misc::Direction::Right;

					player.reachingPoint = sf::Vector2f(1550, player.getPosition().y);
					player.direction = player.reachingPoint - player.getPosition();
					player.movePedSpeed = 0.05f;
					tobias.reachingPoint = sf::Vector2f(1550, tobias.getPosition().y);
					tobias.direction = tobias.reachingPoint - tobias.getPosition();
					tobias.movePedSpeed = 0.05f;
				}
			}
			if (part == 5)
			{
				if (player.getPosition().x <= player.reachingPoint.x)
				{
					player.move(player.movePedSpeed * player.direction * courier.clockMovement.getElapsedTime().asSeconds());
					player.source.x++;
					if (player.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						player.source.x = 0;
				}
				else { player.reachedSpot = true; }
				if (tobias.getPosition().x <= tobias.reachingPoint.x)
				{
					tobias.move(tobias.movePedSpeed * tobias.direction * courier.clockMovement.getElapsedTime().asSeconds());
					tobias.source.x++;
					if (tobias.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						tobias.source.x = 0;
				}
				else { tobias.reachedSpot = true; }
				if (lucius.getPosition().x <= lucius.reachingPoint.x)
				{
					lucius.move(lucius.movePedSpeed * lucius.direction * courier.clockMovement.getElapsedTime().asSeconds());
					lucius.source.x++;
					if (lucius.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						lucius.source.x = 0;
				}
				else { lucius.reachedSpot = true; }
				if (lucius.reachedSpot)
				{
					lucius.reachingPoint = sf::Vector2f(2330, lucius.getPosition().y);
					lucius.direction = lucius.reachingPoint - lucius.getPosition();
					lucius.reachedSpot = false;
					lucius.source.y = Misc::Direction::Right;
					lucius.movePedSpeed = 0.5f;
				}
				if (player.reachedSpot && tobias.reachedSpot)
				{
					part = 6;
					objCurrentText = "Find Lucius.";
					lucius.setPosition(2686, 1797);
					player.source.x = 1;
					tobias.source.x = 1;
					lucius.source.x = 1;
					player.reachedSpot = false;
					tobias.reachedSpot = false;
					lucius.reachedSpot = false;
					continueLucius = false;
					player.frozen = false;
					player.autoMove = false;

					tobias.reachingPoint = sf::Vector2f(2330, tobias.getPosition().y);
					tobias.direction = tobias.reachingPoint - tobias.getPosition();
					tobias.movePedSpeed = 0.75f;
				}
			}
			if (part == 6)
			{
				if (tobias.getPosition().x <= tobias.reachingPoint.x)
				{
					tobias.move(tobias.movePedSpeed * tobias.direction * courier.clockMovement.getElapsedTime().asSeconds());
					tobias.source.x++;
					if (tobias.source.x * 32 >= 96) // 96 = Width of Entire Texture applied to Sprite (not just the Rect)
						tobias.source.x = 0;
				}
				else
				{
					tobias.setPosition(2648, 1792);
					currentObj = 2;
					part = 0;
				}
			}
		}
		else if (currentObj == 2)
		{
			name = "Uncle Trent";
			objCurrentText = "Find Lucius.";

			tobias.setTextureRect(sf::IntRect((int)tobias.source.x * 32, (int)tobias.source.y * 32, 32, 32));
			lucius.setTextureRect(sf::IntRect((int)lucius.source.x * 32, (int)lucius.source.y * 32, 32, 32));
			shadow.setTextureRect(sf::IntRect((int)shadow.source.x * 32, (int)shadow.source.y * 32, 32, 32));

			if (misc.wallHack == false)
			{
				float left = tobias.getGlobalBounds().left - 24;
				float right = left + tobias.getGlobalBounds().width + 16;
				float top = tobias.getGlobalBounds().top - 32;
				float bottom = top + tobias.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}
			if (misc.wallHack == false)
			{
				float left = lucius.getGlobalBounds().left - 24;
				float right = left + lucius.getGlobalBounds().width + 16;
				float top = lucius.getGlobalBounds().top - 32;
				float bottom = top + lucius.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}
			if (misc.wallHack == false)
			{
				float left = shadow.getGlobalBounds().left - 24;
				float right = left + shadow.getGlobalBounds().width + 16;
				float top = shadow.getGlobalBounds().top - 32;
				float bottom = top + shadow.getGlobalBounds().height + 16;
				if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}

			if (misc.wallHack == false)
			{
				if (!(player.getPosition().x > 1240 && player.getPosition().x < 3055 && player.getPosition().y > 1565 && player.getPosition().y < 1840))
					player.setPosition(player.prevPos.x, player.prevPos.y);
			}

			if (part >= 0)
			{
				lucius.setPosition(2686, 1797);
				lucius.source.y = Misc::Direction::Right;
				tobias.setPosition(2648, 1797);
				tobias.source.y = Misc::Direction::Right;
				shadow.setPosition(2782, 1775);
				shadow.source.y = Misc::Direction::Down;
			}
			if (part == 0)
			{
				misc.autoMode = false;
				misc.saveNow = true;
				part = 1;
			}
			else if (part == 1)
			{
			}
		}
		else if (currentObj == 5)
		{
			name = "Did You Get The Memo?";
			if (part == 0)
			{
				objCurrentText = "Go home.";
				part = 1;
			}
			else if (part == 1)
			{
				objCurrentText = "Go home.";
				if (!misc.showArrow) { misc.showArrow = true; misc.arrowFlash = true; }
				if (player.getPosition().x >= 810 && player.getPosition().x <= 851 && player.getPosition().y >= 510 && player.getPosition().y <= 538)
				{
					part = 2;
					courier.setPosition(1395, player.getPosition().y);
					courier.direction = player.getPosition() - courier.getPosition();
					courier.source.x = 1;
				}
			}
			else if (part == 2)
			{
				objCurrentText = "Go home.";
				misc.autoMode = true;
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
					courier.source.x = 1;
					part = 3;
					subPart = 0;
				}
			}
			else if (part == 3)
			{
				objCurrentText = "Go home.";
				misc.autoMode = false;
				player.frozen = true;
				courier.setPosition(player.getPosition().x + 26, player.getPosition().y);
				courier.source.y = Misc::Direction::Left;
				courier.source.x = 1;
				courier.setTextureRect(sf::IntRect((int)courier.source.x * 32, (int)courier.source.y * 32, 32, 32));
				if (subPart == 0)
				{
					misc.textInTextBox = "COURIER: Do you live here? I have a package for this address.";
					misc.showTextBox = true;
				}
				else if (subPart == 1)
				{
					misc.drawInTextBox.setStyle(sf::Text::Italic);
					misc.drawInTextBox_Outline1.setStyle(sf::Text::Italic);
					misc.drawInTextBox_Outline2.setStyle(sf::Text::Italic);
					misc.drawInTextBox_Outline3.setStyle(sf::Text::Italic);
					misc.drawInTextBox_Outline4.setStyle(sf::Text::Italic);
					misc.textInTextBox = "COURIER hands you the package.";
					misc.showTextBox = true;
				}
				else if (subPart == 2)
				{
					misc.drawInTextBox.setStyle(sf::Text::Regular);
					misc.drawInTextBox_Outline1.setStyle(sf::Text::Regular);
					misc.drawInTextBox_Outline2.setStyle(sf::Text::Regular);
					misc.drawInTextBox_Outline3.setStyle(sf::Text::Regular);
					misc.drawInTextBox_Outline4.setStyle(sf::Text::Regular);
					misc.textInTextBox = "COURIER: Sign here with your name.";
					misc.showTextBox = true;
				}
				else if (subPart == 3)
				{
					objCurrentText = "Sign with your name.";
					misc.showSignBox = true;
					misc.showTextBox = false;
					misc.typing = true;
				}
			}
		}
		else if (currentObj == 6)
		{
			name = "Did You Get The Memo?";
			if (part == 0)
			{
				objCurrentText = "None.";
			}
		}
		else
		{
			currentObj = -1;
			name = "None";
			objCurrentText = "None.";
		}
	}
}