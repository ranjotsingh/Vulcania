#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <functional>
#include <thread>

#include "Player.h"
#include "Menu.h"
#include "Misc.h"
#include "Objects.h"
#include "Buildings.h"
#include "Objective.h"
#include "Ped.h"

void loadingScreen(sf::RenderWindow &Window, Misc &misc)
{
	sf::Text textLoading("Loading...", misc.fontNoodle, 20);
	textLoading.setPosition((misc.screenDimensions.x - textLoading.getGlobalBounds().width) / 2, misc.screenDimensions.y - 65);
	misc.smooth(textLoading);
	Window.draw(textLoading);
	Window.display();
}

void inputs(Misc &misc, Player &player, Objective &objective, Ped &tobias, Ped &lucius, Ped &courier)
{
	std::string input;
	while (std::cin >> input)
	{
		if (Misc::GameState::InGame)
		{
			if (input == "wallhack" && misc.wallHack == false)
			{
				misc.wallHack = true;
				std::cout << "*** Wallhack activated." << std::endl;
			}
			else if (input == "wallhack" && misc.wallHack == true)
			{
				misc.wallHack = false;
				std::cout << "*** Wallhack deactivated." << std::endl;
			}
			else if (input == "reset")
			{
				objective.currentObj = 0;
				objective.part = 0;
				misc.typing = false;
				std::cout << "*** Game reset." << std::endl;
			}
			else if (input == "skip")
			{
				player.setPosition(818, 1055);
				tobias.setPosition(818, 1088);
				lucius.setPosition(706, 1068);
				std::cout << "*** Skipped." << std::endl;
			}
			else if (input == "info")
			{
				std::cout << "*** Position: (" << player.getPosition().x << ", " << player.getPosition().y << ") | player.moving: " << player.moving << " | player.frozen: " << player.frozen << std::endl;
				std::cout << "*** objective.currentObj: " << objective.currentObj << " | objective.part: " << objective.part << " | objective.subPart: " << objective.subPart << std::endl;
				std::cout << courier.source.x << std::endl;
			}
			else if (input == "teleport")
			{
				float x, y;
				std::cout << "*** Teleport - X: ";
				std::cin >> x;
				std::cout << "*** Teleport - Y: ";
				std::cin >> y;
				player.setPosition(x, y);
			}
			else if (input == "freeroam")
			{
				objective.currentObj = -1;
				objective.part = 0;
				objective.subPart = 0;
				misc.typing = false;
				player.wasFrozen = false;
				player.autoMove = false;
				std::cout << "*** Objectives disabled." << std::endl;
			}
			else if (input == "setobjective")
			{
				std::cout << "*** Set current objective to: ";
				std::cin >> objective.currentObj;
				objective.part = 0;
				objective.subPart = 0;
				misc.typing = false;
				std::cout << "*** Objective set to " << objective.currentObj << "." << std::endl;
			}
			else { std::cout << "*** Invalid command." << std::endl; }
		}
	}
}

int main()
{
	Misc misc;
	Menu menu;
	Player player;
	Objects objects;
	Buildings buildings;
	Objective objective;

	Ped courier;
	Ped lucius;
	Ped shadow;
	Ped tobias;

	std::cout << "*** " << misc.gameName << " is now running." << std::endl;

	sf::Clock clock;
	sf::Clock clockMenu;
	sf::Clock clockFlash;
	sf::Clock totalGameTime;

	int backgroundCurrentFrame = 0;

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	float frameMenuCounter = 0, switchMenuFrame = 100, frameMenuSpeed = 1500;
	float framePedMovementCounter = 0, switchPedMovementFrame = 100, framePedMovementSpeed = 500;
	float frameFlashCounter = 0, switchFlashFrame = 100, frameFlashSpeed = 400;

	sf::Image icon;
	icon.loadFromFile("images/misc/icon.png");

	sf::RenderWindow Window;
	Window.create(sf::VideoMode((int)misc.screenDimensions.x, (int)misc.screenDimensions.y), misc.gameName, sf::Style::Titlebar | sf::Style::Close);
	Window.setFramerateLimit(100);
	Window.setKeyRepeatEnabled(false);
	Window.setIcon(256, 256, icon.getPixelsPtr());
	Window.setActive(false);

	sf::Thread loadingThread(std::bind(loadingScreen, std::ref(Window), std::ref(misc)));
	loadingThread.launch();

	std::string saveFileName = "save/save001.sav";
	std::ifstream saveFile(saveFileName);
	bool SavedGameExists;
	if (saveFile)
		SavedGameExists = true;
	else
		SavedGameExists = false;

	sf::Texture pTexture;
	sf::Texture mTexture;
	sf::Sprite map;
	sf::Texture bTexture;
	sf::Sprite background;
	sf::Texture lTexture;
	sf::Sprite logo;
	sf::Texture lnTexture;
	sf::Sprite logoname;
	sf::Texture signsTexture;
	sf::Texture boxesTexture;
	sf::Sprite arrow;
	sf::Sprite exclaim;
	sf::Sprite objectivebox;
	sf::Sprite signbox;

	sf::Texture pedCourierTexture;
	sf::Texture pedLuciusTexture;
	sf::Texture pedShadowTexture;
	sf::Texture pedTobiasTexture;

	sf::Texture Building;
	sf::Texture Floor;
	sf::Texture Floor2;
	sf::Texture Floor3;
	sf::Texture Background;
	sf::Texture Object;
	sf::Texture BoundaryV;
	sf::Texture BoundaryH;

	sf::Sprite Grass;
	misc.loadFloor(Floor, Grass);

	sf::Sprite DirtH0;
	misc.loadFloor(Floor2, DirtH0);
	sf::Sprite DirtH1;
	misc.loadFloor(Floor2, DirtH1);
	sf::Sprite DirtH2;
	misc.loadFloor(Floor2, DirtH2);
	sf::Sprite DirtH3;
	misc.loadFloor(Floor2, DirtH3);

	sf::Sprite DirtV0;
	misc.loadFloor(Floor3, DirtV0);

	sf::Sprite Grey;
	misc.loadBackground(Background, Grey);

	sf::Sprite MainHouse;
	buildings.load(Building, MainHouse);

	sf::Sprite House0;
	buildings.load(Building, House0);
	sf::Sprite House1;
	buildings.load(Building, House1);
	sf::Sprite House2;
	buildings.load(Building, House2);
	sf::Sprite House3;
	buildings.load(Building, House3);
	sf::Sprite House4;
	buildings.load(Building, House4);

	sf::Sprite Object0;
	objects.load(Object, Object0);
	sf::Sprite Object1;
	objects.load(Object, Object1);
	sf::Sprite Object2;
	objects.load(Object, Object2);
	sf::Sprite Object3;
	objects.load(Object, Object3);
	sf::Sprite Object4;
	objects.load(Object, Object4);
	sf::Sprite Object5;
	objects.load(Object, Object5);
	sf::Sprite Object6;
	objects.load(Object, Object6);
	sf::Sprite Object7;
	objects.load(Object, Object7);

	sf::Sprite BoundaryV0;
	misc.loadBoundaryV(BoundaryV, BoundaryV0);
	sf::Sprite BoundaryV1;
	misc.loadBoundaryV(BoundaryV, BoundaryV1);
	sf::Sprite BoundaryV2;
	misc.loadBoundaryV(BoundaryV, BoundaryV2);
	sf::Sprite BoundaryV3;
	misc.loadBoundaryV(BoundaryV, BoundaryV3);

	sf::Sprite BoundaryH0;
	misc.loadBoundaryH(BoundaryH, BoundaryH0);
	sf::Sprite BoundaryH1;
	misc.loadBoundaryH(BoundaryH, BoundaryH1);
	sf::Sprite BoundaryH2;
	misc.loadBoundaryH(BoundaryH, BoundaryH2);
	sf::Sprite BoundaryH3;
	misc.loadBoundaryH(BoundaryH, BoundaryH3);
	sf::Sprite BoundaryH4;
	misc.loadBoundaryH(BoundaryH, BoundaryH4);
	sf::Sprite BoundaryH5;
	misc.loadBoundaryH(BoundaryH, BoundaryH5);
	sf::Sprite BoundaryH6;
	misc.loadBoundaryH(BoundaryH, BoundaryH6);

	sf::View view;

	view.reset(sf::FloatRect(0, 0, misc.screenDimensions.x, misc.screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	bool updateFrame = true;
	bool updateMenuFrame = true;
	bool updatePedMovementFrame = true;
	bool updateFlashFrame = true;

	if (!pTexture.loadFromFile("images/peds/Player.png")) { std::cout << "*** Error: Game failed to load 'Player' image." << std::endl; }

	if (!mTexture.loadFromFile("images/map/Map.png")) { std::cout << "*** Error: Game failed to load 'Map' image." << std::endl; }
	if (!bTexture.loadFromFile("images/misc/Background.png")) { std::cout << "*** Error: Game failed to load 'Background' image." << std::endl; }
	if (!lTexture.loadFromFile("images/misc/Logo.png")) { std::cout << "*** Error: Game failed to load 'Logo' image." << std::endl; }
	if (!lnTexture.loadFromFile("images/misc/Logoname.png")) { std::cout << "*** Error: Game failed to load 'Logoname' image." << std::endl; }
	if (!signsTexture.loadFromFile("images/misc/signs.png")) { std::cout << "*** Error: Game failed to load 'signs' image." << std::endl; }
	if (!boxesTexture.loadFromFile("images/boxes/boxes.png")) { std::cout << "*** Error: Game failed to load 'boxes' image." << std::endl; }

	if (!pedCourierTexture.loadFromFile("images/peds/Courier.png")) { std::cout << "*** Error: Game failed to load 'Courier' image." << std::endl; }
	if (!pedLuciusTexture.loadFromFile("images/peds/WhiteWolf.png")) { std::cout << "*** Error: Game failed to load 'WhiteWolf' image." << std::endl; }
	if (!pedShadowTexture.loadFromFile("images/peds/BlackWolf.png")) { std::cout << "*** Error: Game failed to load 'BlackWolf' image." << std::endl; }
	if (!pedTobiasTexture.loadFromFile("images/peds/Tobias.png")) { std::cout << "*** Error: Game failed to load 'Tobias' image." << std::endl; }

	if (!Background.loadFromFile("images/misc/grey.png")) { std::cout << "*** Error: Game failed to load 'grey' image." << std::endl; }

	if (!Building.loadFromFile("images/map/buildings.png")) { std::cout << "*** Error: Game failed to load 'buildings' image." << std::endl; }
	if (!Object.loadFromFile("images/map/misc.png")) { std::cout << "*** Error: Game failed to load 'misc' image." << std::endl; }

	if (!Floor.loadFromFile("images/map/floor.png")) { std::cout << "*** Error: Game failed to load 'floor' image." << std::endl; }
	if (!Floor2.loadFromFile("images/map/dirt.png")) { std::cout << "*** Error: Game failed to load 'dirt' image." << std::endl; }
	if (!Floor3.loadFromFile("images/map/dirt2.png")) { std::cout << "*** Error: Game failed to load 'dirt2' image." << std::endl; }

	player.setTexture(pTexture);
	player.setPosition(620, 590);

	map.setTexture(mTexture);

	background.setTexture(bTexture);

	logo.setTexture(lTexture);
	logo.setPosition((misc.screenDimensions.x - logo.getGlobalBounds().width) / 2, (misc.screenDimensions.y - logo.getGlobalBounds().height) / 2);

	logoname.setTexture(lnTexture);
	logoname.setPosition((misc.screenDimensions.x - logoname.getGlobalBounds().width) / 2, 200);

	arrow.setTexture(signsTexture);
	arrow.setTextureRect(sf::IntRect(0, 0, 10, 18));
	arrow.setPosition(852, 515);
	arrow.setRotation(180);

	exclaim.setTexture(signsTexture);
	exclaim.setTextureRect(sf::IntRect(15, 0, 20, 20));

	objectivebox.setTexture(boxesTexture);
	objectivebox.setTextureRect(sf::IntRect(0, 0, 200, 81));
	objectivebox.setPosition(misc.screenDimensions.x - objectivebox.getGlobalBounds().width - 10, misc.screenDimensions.y - 75);

	signbox.setTexture(boxesTexture);
	signbox.setTextureRect(sf::IntRect(0, 147, 331, 488));
	signbox.setPosition((misc.screenDimensions.x - signbox.getGlobalBounds().width) / 2, (misc.screenDimensions.y - signbox.getGlobalBounds().height) / 2);

	courier.setTexture(pedCourierTexture);
	lucius.setTexture(pedLuciusTexture);
	shadow.setTexture(pedShadowTexture);
	tobias.setTexture(pedTobiasTexture);

	sf::String startingPressSpace = "Press space to start game.";
	sf::Text textPressSpace(startingPressSpace, misc.fontNoodle, 20);
	textPressSpace.setColor(sf::Color(255, 255, 255));
	textPressSpace.setPosition((misc.screenDimensions.x - textPressSpace.getGlobalBounds().width) / 2, misc.screenDimensions.y - 65);
	misc.smooth(textPressSpace);

	menu.textNewGame.setFont(misc.fontNoodle);
	menu.textContinueGame.setFont(misc.fontNoodle);
	menu.textOptions.setFont(misc.fontNoodle);
	menu.textQuit.setFont(misc.fontNoodle);
	menu.textMenuVersion.setFont(misc.fontNoodle);
	menu.draw(misc);

	misc.drawInTextBox.setFont(misc.fontMain);
	misc.drawInTextBox_Outline1.setFont(misc.fontMain);
	misc.drawInTextBox_Outline2.setFont(misc.fontMain);
	misc.drawInTextBox_Outline3.setFont(misc.fontMain);
	misc.drawInTextBox_Outline4.setFont(misc.fontMain);
	misc.loadTextBox();
	misc.textbox.setTexture(boxesTexture);

	sf::Text textGameObjective(objective.name, misc.fontMain, 19);
	textGameObjective.setColor(sf::Color(255, 215, 0));
	textGameObjective.setStyle(sf::Text::Underlined);
	textGameObjective.setPosition((objectivebox.getLocalBounds().width - textGameObjective.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, misc.screenDimensions.y - 75);
	misc.smooth(textGameObjective);
	sf::Text textGameObjective_Outline1(objective.name, misc.fontMain, textGameObjective.getCharacterSize());
	textGameObjective_Outline1.setColor(sf::Color(0, 0, 0));
	textGameObjective_Outline1.setStyle(sf::Text::Underlined);
	textGameObjective_Outline1.setPosition(textGameObjective.getPosition().x - 1, textGameObjective.getPosition().y);
	misc.smooth(textGameObjective_Outline1);
	sf::Text textGameObjective_Outline2(objective.name, misc.fontMain, textGameObjective.getCharacterSize());
	textGameObjective_Outline2.setColor(sf::Color(0, 0, 0));
	textGameObjective_Outline2.setStyle(sf::Text::Underlined);
	textGameObjective_Outline2.setPosition(textGameObjective.getPosition().x + 1, textGameObjective.getPosition().y);
	misc.smooth(textGameObjective_Outline2);
	sf::Text textGameObjective_Outline3(objective.name, misc.fontMain, textGameObjective.getCharacterSize());
	textGameObjective_Outline3.setColor(sf::Color(0, 0, 0));
	textGameObjective_Outline3.setStyle(sf::Text::Underlined);
	textGameObjective_Outline3.setPosition(textGameObjective.getPosition().x, textGameObjective.getPosition().y - 1);
	misc.smooth(textGameObjective_Outline3);
	sf::Text textGameObjective_Outline4(objective.name, misc.fontMain, textGameObjective.getCharacterSize());
	textGameObjective_Outline4.setColor(sf::Color(0, 0, 0));
	textGameObjective_Outline4.setStyle(sf::Text::Underlined);
	textGameObjective_Outline4.setPosition(textGameObjective.getPosition().x, textGameObjective.getPosition().y + 1);
	misc.smooth(textGameObjective_Outline4);

	sf::Text textgameObjectiveCurrent(objective.objCurrentText, misc.fontMain, 18);
	textgameObjectiveCurrent.setColor(sf::Color(255, 255, 255));
	textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);
	misc.smooth(textgameObjectiveCurrent);
	sf::Text textgameObjectiveCurrent_Outline1(objective.objCurrentText, misc.fontMain, textgameObjectiveCurrent.getCharacterSize());
	textgameObjectiveCurrent_Outline1.setColor(sf::Color(0, 0, 0));
	textgameObjectiveCurrent_Outline1.setPosition(textgameObjectiveCurrent.getPosition());
	misc.smooth(textgameObjectiveCurrent_Outline1);
	sf::Text textgameObjectiveCurrent_Outline2(objective.objCurrentText, misc.fontMain, textgameObjectiveCurrent.getCharacterSize());
	textgameObjectiveCurrent_Outline2.setColor(sf::Color(0, 0, 0));
	textgameObjectiveCurrent_Outline2.setPosition(textgameObjectiveCurrent.getPosition());
	misc.smooth(textgameObjectiveCurrent_Outline2);
	sf::Text textgameObjectiveCurrent_Outline3(objective.objCurrentText, misc.fontMain, textgameObjectiveCurrent.getCharacterSize());
	textgameObjectiveCurrent_Outline3.setColor(sf::Color(0, 0, 0));
	textgameObjectiveCurrent_Outline3.setPosition(textgameObjectiveCurrent.getPosition());
	misc.smooth(textgameObjectiveCurrent_Outline3);
	sf::Text textgameObjectiveCurrent_Outline4(objective.objCurrentText, misc.fontMain, textgameObjectiveCurrent.getCharacterSize());
	textgameObjectiveCurrent_Outline4.setColor(sf::Color(0, 0, 0));
	textgameObjectiveCurrent_Outline4.setPosition(textgameObjectiveCurrent.getPosition());
	misc.smooth(textgameObjectiveCurrent_Outline4);

	sf::Text text("", misc.fontDaniel, 20);
	text.setColor(sf::Color(0, 0, 0));
	sf::String sentence;

	sf::Thread inputThread(std::bind(&inputs, std::ref(misc), std::ref(player), std::ref(objective), std::ref(tobias), std::ref(lucius), std::ref(courier)));
	inputThread.launch();

	loadingThread.terminate();
	std::cout << "*** Load Time: " << totalGameTime.getElapsedTime().asSeconds() + 0.7 << " seconds.\n\n";

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			if (misc.gamestate == Misc::GameState::StartMenu)
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Space)
					{
						misc.gamestate = Misc::GameState::MainMenu;
						menu.textNewGame.setColor(sf::Color(204, 204, 0));
						menu.textContinueGame.setColor(sf::Color(204, 204, 0));
					}
				}
			}
			else if (misc.gamestate == Misc::GameState::MainMenu || misc.paused == true)
			{
				menu.navigate();
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Return)
					{
						if (menu.Option == menu.optionStartGame)
						{
							misc.gamestate = Misc::GameState::InGame;
							misc.paused = false;
							if (player.wasFrozen == false) { player.frozen = false; }
							updateMenuFrame = false;
							if (!SavedGameExists)
							{
								std::ofstream file(saveFileName);
							}
							if (objective.currentObj == 5 && objective.part == 0)
							{
								misc.showArrow = true;
								misc.arrowFlash = true;
							}
						}
						else if (menu.Option == menu.optionQuit)
						{
							if (misc.gamestate == Misc::GameState::MainMenu)
							{
								inputThread.terminate();
								Window.close();
								exit(0);
							}
							else if (misc.paused == true)
							{
								misc.gamestate = Misc::GameState::MainMenu;
								misc.paused = false;
								menu.Option = menu.optionStartGame;
								menu.textNewGame.setColor(sf::Color(204, 204, 0));
								menu.textContinueGame.setColor(sf::Color(204, 204, 0));
								menu.textQuit.setColor(sf::Color(255, 255, 255));
								Window.setView(Window.getDefaultView());
								updateMenuFrame = true;
							}
						}
					}
				}
			}
			else if (misc.gamestate == Misc::GameState::InGame && misc.paused == false)
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if ((Event.key.code == sf::Keyboard::P || Event.key.code == sf::Keyboard::Escape) && misc.typing == false)
					{
						if (player.frozen == true)
						{
							player.wasFrozen = true;
						}
						else
						{
							player.wasFrozen = false;
						}
						misc.paused = true;
						player.frozen = true;
						menu.textContinueGame.setColor(sf::Color(204, 204, 0));
					}
					else if (Event.key.code == sf::Keyboard::Space)
					{
						if (objective.currentObj == 5 && objective.part == 3 && objective.subPart >= 0 && objective.subPart <= 2)
						{
							objective.subPart += 1;
						}
					}
					else if (Event.key.code == sf::Keyboard::Return)
					{
						if (objective.currentObj == 5 && objective.part == 3 && objective.subPart == 3)
						{
							sentence.erase(0, 1);
							player.name = sentence.toAnsiString();
							std::cout << "*** Player name has been set to '" << player.name << "'." << std::endl;
							std::cout << "*** Game has saved information into the game save file." << std::endl;
							misc.showSignBox = false;
							player.frozen = false;
							objective.currentObj++;
							objective.part = 0;
							misc.typing = false;
						}
					}
				}
				else if (Event.type == sf::Event::TextEntered)
				{
					if (objective.currentObj == 5 && objective.part == 3 && objective.subPart == 3)
					{
						if (Event.text.unicode == 32 || Event.text.unicode == 39 || (Event.text.unicode >= 65 && Event.text.unicode <= 90) || (Event.text.unicode >= 97 && Event.text.unicode <= 122))
						{
							if (text.getGlobalBounds().width <= 300)
								sentence += (char)Event.text.unicode;
						}
						else if (Event.text.unicode == 8 && sentence.getSize() > 0)
							sentence.erase(sentence.getSize() - 1, sentence.getSize());

						text.setString(sentence);
						text.setPosition(signbox.getLocalBounds().width + 30, signbox.getLocalBounds().height + 85);
					}
				}
			}

			/*if (misc.gamestate == Misc::GameState::InGame && misc.paused == true)
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Return)
					{
						misc.paused = false;
						if (player.wasFrozen == false) { player.frozen = false; }
					}
				}
			}*/

			switch (Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				exit(0);
				break;
			/*
			case sf::Event::TextEntered:
				if(Event.text.unicode >= 32 && Event.text.unicode <= 126)
				sentence +=(char)Event.text.unicode;
				else if(Event.text.unicode == 8 && sentence.getSize() > 0)
				sentence.erase(sentence.getSize() - 1, sentence.getSize());
				text.setString(sentence);
				text.getGlobalBounds().width;
				break;
			*/
			//case sf::Event::MouseMoved:
				//std::cout << "X: " << Event.mouseMove.x << " Y: " << Event.mouseMove.y << std::endl;
				//std::cout << "Total Game Time: " << totalGameTime.getElapsedTime().asSeconds() << std::endl;
				//std::cout << "Menu Option: " << menu.Option << std::endl;
				//std::cout << "Left: " << logo.getGlobalBounds().left << " Right: " << logo.getGlobalBounds().left + logo.getGlobalBounds().width << " Top: " << logo.getGlobalBounds().top << " Bottom: " << logo.getGlobalBounds().top + logo.getGlobalBounds().height << std::endl;
			}
		}

		player.prevPos.x = player.getPosition().x;
		player.prevPos.y = player.getPosition().y;

		if (misc.gamestate == Misc::GameState::InGame && player.frozen == false && player.autoMove == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				player.running = true;
				player.moveSpeed = 200.0f;
				frameSpeed = 1000;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				player.running = true;
				player.moveSpeed = 500.0f;
				frameSpeed = 10000;
			}
			else
			{
				player.running = false;
				player.moveSpeed = 100.0f;
				frameSpeed = 500;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.source.y = Misc::Direction::Up;
				player.moving = true;
				if (player.getPosition().y >= 0)
					player.move(0, -player.moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.source.y = Misc::Direction::Down;
				player.moving = true;
				player.move(0, player.moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.source.y = Misc::Direction::Right;
				player.moving = true;
				player.move(player.moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.source.y = Misc::Direction::Left;
				player.moving = true;
				if (player.getPosition().x >= 0)
					player.move(-player.moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
			else if (player.autoMove == false)
			{
				player.moving = false;
				player.source.x = 1;
			}
		}

		if (player.frozen == true && player.autoMove == false)
		{
			player.moving = false;
			player.source.x = 1;
		}

		if (misc.gamestate == Misc::GameState::InGame && misc.showTextBox == true && misc.paused == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				misc.showTextBox = false;
				player.frozen = false;
			}
		}

		if (Window.hasFocus() == false && misc.gamestate == Misc::GameState::InGame && misc.paused == false)
		{
			if (player.frozen == true)
			{
				player.wasFrozen = true;
			}
			else
			{
				player.wasFrozen = false;
			}
			misc.paused = true;
			player.frozen = true;
			menu.textContinueGame.setColor(sf::Color(204, 204, 0));
		}

		objective.initiate(misc, player, tobias, lucius, courier, shadow);

		frameCounter = (updateFrame) ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;
		if (frameCounter >= switchFrame && player.moving == true)
		{
			frameCounter = 0;
			player.source.x++;
			if (player.source.x * 32 >= (int)pTexture.getSize().x)
				player.source.x = 0;
		}

		framePedMovementCounter = (updatePedMovementFrame) ? framePedMovementCounter + framePedMovementSpeed * courier.clockMovement.restart().asSeconds() : 0;
		if (framePedMovementCounter >= switchPedMovementFrame)
		{
			framePedMovementCounter = 0;
		}

		// Drawing the map textures
		misc.drawFloor("Grass", Floor, Grass, 0, 0, 0, 50000, 50000);
		misc.drawFloor("DirtH0", Floor2, DirtH0, 0, 610, 540, Floor2.getSize().x * 15, Floor2.getSize().y * 1);
		misc.drawFloor("DirtH1", Floor2, DirtH1, 0, 610, 1618, Floor2.getSize().x * 60, Floor2.getSize().y * 1);
		misc.drawFloor("DirtH2", Floor2, DirtH2, 0, 610, 1056, Floor2.getSize().x * 60, Floor2.getSize().y * 1);
		misc.drawFloor("DirtH3", Floor2, DirtH3, 0, 610, 702, Floor2.getSize().x * 10, Floor2.getSize().y * 1);
		misc.drawFloor("DirtV0", Floor3, DirtV0, 0, 608, 542, Floor3.getSize().x * 1, Floor3.getSize().y * 25);

		misc.drawBackground("Grey", Background, Grey, 0, 0, 0, misc.screenDimensions.x, misc.screenDimensions.y);

		buildings.draw(misc, player, "Main House", Building, MainHouse, 0, 760, 420);
		buildings.draw(misc, player, "House0", Building, House0, 1, 928, 431);
		buildings.draw(misc, player, "House1", Building, House1, 2, 1072, 451);
		buildings.draw(misc, player, "House2", Building, House2, 3, 787, 637);
		buildings.draw(misc, player, "House3", Building, House3, 4, 884, 608);
		buildings.draw(misc, player, "House4", Building, House4, 5, 1027, 604);
		buildings.spawnDoors(misc, player);

		objects.draw(misc, player, "Tree0", Object, Object0, 0, 693, 613, true);
		objects.draw(misc, player, "Tree1", Object, Object4, 0, 2425, 1688, true);
		objects.draw(misc, player, "Tree2", Object, Object5, 0, 2535, 1688, true);
		objects.draw(misc, player, "Tree2", Object, Object6, 0, 2645, 1688, true);
		objects.draw(misc, player, "Tree3", Object, Object7, 0, 2755, 1688, true);
		objects.draw(misc, player, "DeadUncle", Object, Object1, 3, 2773, 1796, true);
		objects.draw(misc, player, "Bush0", Object, Object2, 4, 2377, 1721, true);
		objects.draw(misc, player, "Bush1", Object, Object3, 4, 2555, 1721, true);

		misc.drawBoundaryV(player, "BoundaryV0", BoundaryV, BoundaryV0, 0, 0);
		misc.drawBoundaryV(player, "BoundaryV1", BoundaryV, BoundaryV1, 0, 1000);
		misc.drawBoundaryV(player, "BoundaryV2", BoundaryV, BoundaryV2, 2304, 1870);
		misc.drawBoundaryV(player, "BoundaryV3", BoundaryV, BoundaryV3, 2875, 1690);

		misc.drawBoundaryH(player, "BoundaryH0", BoundaryH, BoundaryH0, 575, 0);
		misc.drawBoundaryH(player, "BoundaryH1", BoundaryH, BoundaryH1, 1150, 0);
		misc.drawBoundaryH(player, "BoundaryH2", BoundaryH, BoundaryH2, 700, 1123);
		misc.drawBoundaryH(player, "BoundaryH3", BoundaryH, BoundaryH3, 700, 1700);
		misc.drawBoundaryH(player, "BoundaryH4", BoundaryH, BoundaryH4, 1502, 1123);
		misc.drawBoundaryH(player, "BoundaryH5", BoundaryH, BoundaryH5, 1502, 1700);
		misc.drawBoundaryH(player, "BoundaryH6", BoundaryH, BoundaryH6, 2308, 1123);

		frameFlashCounter = (updateFlashFrame) ? frameFlashCounter + frameFlashSpeed * clockFlash.restart().asSeconds() : 0;
		if (frameFlashCounter >= switchFlashFrame && misc.showArrow == true)
		{
			frameFlashCounter = 0;
			if (misc.arrowFlash == true)
				misc.arrowFlash = false;
			else
				misc.arrowFlash = true;
		}

		frameMenuCounter = (updateMenuFrame) ? frameMenuCounter + frameMenuSpeed * clockMenu.restart().asSeconds() : 0;
		if (frameMenuCounter >= switchMenuFrame)
		{
			frameMenuCounter = 0;
			if (backgroundCurrentFrame >= 0 && backgroundCurrentFrame <= 5)
				backgroundCurrentFrame++;
			else if (backgroundCurrentFrame >= 6)
				backgroundCurrentFrame = 0;
		}

		if (misc.gamestate == Misc::GameState::InGame) { view.setCenter(player.getPosition()); }

		Window.setView(view);

		player.setTextureRect(sf::IntRect(player.source.x * 32, player.source.y * 32, 32, 32));
		background.setTextureRect(sf::IntRect(0, backgroundCurrentFrame * 600, (int)misc.screenDimensions.x, (int)misc.screenDimensions.y));

		misc.drawInTextBox.setString(misc.textInTextBox);
		misc.drawInTextBox.setPosition((misc.textbox.getLocalBounds().width - misc.drawInTextBox.getGlobalBounds().width) / 2 + misc.textbox.getPosition().x, misc.screenDimensions.y - 30);
		misc.smooth(misc.drawInTextBox);
		misc.drawInTextBox_Outline1.setString(misc.textInTextBox);
		misc.drawInTextBox_Outline1.setPosition(misc.drawInTextBox.getPosition().x + 1, misc.drawInTextBox.getPosition().y);
		misc.smooth(misc.drawInTextBox_Outline1);
		misc.drawInTextBox_Outline2.setString(misc.textInTextBox);
		misc.drawInTextBox_Outline2.setPosition(misc.drawInTextBox.getPosition().x - 1, misc.drawInTextBox.getPosition().y);
		misc.smooth(misc.drawInTextBox_Outline2);
		misc.drawInTextBox_Outline3.setString(misc.textInTextBox);
		misc.drawInTextBox_Outline3.setPosition(misc.drawInTextBox.getPosition().x, misc.drawInTextBox.getPosition().y - 1);
		misc.smooth(misc.drawInTextBox_Outline3);
		misc.drawInTextBox_Outline4.setString(misc.textInTextBox);
		misc.drawInTextBox_Outline4.setPosition(misc.drawInTextBox.getPosition().x, misc.drawInTextBox.getPosition().y + 1);
		misc.smooth(misc.drawInTextBox_Outline4);

		textGameObjective.setString(objective.name);
		textGameObjective.setPosition((objectivebox.getLocalBounds().width - textGameObjective.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, misc.screenDimensions.y - 75);
		misc.smooth(textGameObjective);
		textGameObjective_Outline1.setString(objective.name);
		textGameObjective_Outline1.setPosition(textGameObjective.getPosition().x - 1, textGameObjective.getPosition().y);
		misc.smooth(textGameObjective_Outline1);
		textGameObjective_Outline2.setString(objective.name);
		textGameObjective_Outline2.setPosition(textGameObjective.getPosition().x + 1, textGameObjective.getPosition().y);
		misc.smooth(textGameObjective_Outline2);
		textGameObjective_Outline3.setString(objective.name);
		textGameObjective_Outline3.setPosition(textGameObjective.getPosition().x, textGameObjective.getPosition().y - 1);
		misc.smooth(textGameObjective_Outline3);
		textGameObjective_Outline4.setString(objective.name);
		textGameObjective_Outline4.setPosition(textGameObjective.getPosition().x, textGameObjective.getPosition().y + 1);
		misc.smooth(textGameObjective_Outline4);

		textgameObjectiveCurrent.setString(objective.objCurrentText);
		textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);
		misc.smooth(textgameObjectiveCurrent);
		textgameObjectiveCurrent_Outline1.setString(objective.objCurrentText);
		textgameObjectiveCurrent_Outline1.setPosition(textgameObjectiveCurrent.getPosition().x - 1, textgameObjectiveCurrent.getPosition().y);
		misc.smooth(textgameObjectiveCurrent_Outline1);
		textgameObjectiveCurrent_Outline2.setString(objective.objCurrentText);
		textgameObjectiveCurrent_Outline2.setPosition(textgameObjectiveCurrent.getPosition().x + 1, textgameObjectiveCurrent.getPosition().y);
		misc.smooth(textgameObjectiveCurrent_Outline2);
		textgameObjectiveCurrent_Outline3.setString(objective.objCurrentText);
		textgameObjectiveCurrent_Outline3.setPosition(textgameObjectiveCurrent.getPosition().x, textgameObjectiveCurrent.getPosition().y - 1);
		misc.smooth(textgameObjectiveCurrent_Outline3);
		textgameObjectiveCurrent_Outline4.setString(objective.objCurrentText);
		textgameObjectiveCurrent_Outline4.setPosition(textgameObjectiveCurrent.getPosition().x, textgameObjectiveCurrent.getPosition().y + 1);
		misc.smooth(textgameObjectiveCurrent_Outline4);

		if (misc.gamestate == Misc::GameState::StartMenu)
		{
			Window.draw(textPressSpace);
			Window.draw(logo);
		}
		else if (misc.gamestate == Misc::GameState::MainMenu)
		{
			Window.setView(Window.getDefaultView());
			//Window.draw(background);
			Window.draw(logoname);
			Window.draw(menu.textMenuVersion);
			if (objective.currentObj <= 1)
			{
				Window.draw(menu.textNewGame);
			}
			else
			{
				Window.draw(menu.textContinueGame);
			}
			Window.draw(menu.textOptions);
			Window.draw(menu.textQuit);
		}
		else if (misc.gamestate == Misc::GameState::InGame)
		{
			Window.draw(Grass);

			Window.draw(DirtH0);
			Window.draw(DirtH1);
			Window.draw(DirtH2);
			Window.draw(DirtH3);
			Window.draw(DirtV0);

			Window.draw(BoundaryV0);
			Window.draw(BoundaryV1);
			Window.draw(BoundaryV2);
			Window.draw(BoundaryV3);

			Window.draw(BoundaryH0);
			Window.draw(BoundaryH1);
			Window.draw(BoundaryH2);
			Window.draw(BoundaryH3);
			Window.draw(BoundaryH4);
			Window.draw(BoundaryH5);
			Window.draw(BoundaryH6);

			Window.draw(MainHouse);
			Window.draw(House0);
			Window.draw(House1);
			Window.draw(House2);
			Window.draw(House3);
			Window.draw(House4);

			Window.draw(Object0);
			Window.draw(Object2);
			Window.draw(Object3);
			Window.draw(Object4);
			Window.draw(Object5);
			Window.draw(Object6);
			Window.draw(Object7);
			if (objective.currentObj >= 0 && objective.currentObj <= 2)
			{
				Window.draw(Object1);
				Window.draw(lucius);
				Window.draw(shadow);
				Window.draw(tobias);
			}
			if (objective.currentObj == 5 && objective.part >= 2) { Window.draw(courier); }
			if (misc.arrowFlash == true && misc.showArrow == true && misc.paused == false) { Window.draw(arrow); }
			if (misc.showExclaim == true)
			{
				exclaim.setPosition(player.getPosition().x + 8, player.getPosition().y - 25);
				Window.draw(exclaim);
			}
			Window.draw(player);

			Window.setView(Window.getDefaultView());
			if (misc.showTextBox == true)
			{
				//Window.draw(misc.textbox);
				Window.draw(misc.drawInTextBox_Outline1);
				Window.draw(misc.drawInTextBox_Outline2);
				Window.draw(misc.drawInTextBox_Outline3);
				Window.draw(misc.drawInTextBox_Outline4);
				Window.draw(misc.drawInTextBox);
			}
			if (misc.showObjectiveBox == true)
			{
				//Window.draw(objectivebox);
				Window.draw(textGameObjective_Outline1);
				Window.draw(textGameObjective_Outline2);
				Window.draw(textGameObjective_Outline3);
				Window.draw(textGameObjective_Outline4);
				Window.draw(textGameObjective);
				if (objective.currentObj >= -1) {
					Window.draw(textgameObjectiveCurrent_Outline1);
					Window.draw(textgameObjectiveCurrent_Outline2);
					Window.draw(textgameObjectiveCurrent_Outline3);
					Window.draw(textgameObjectiveCurrent_Outline4);
					Window.draw(textgameObjectiveCurrent);
				}
			}
			if (misc.showSignBox == true)
			{
				Window.draw(signbox);
				Window.draw(text);
			}
			if (misc.paused == true)
			{
				Window.draw(Grey);
				Window.draw(logoname);
				Window.draw(menu.textContinueGame);
				Window.draw(menu.textOptions);
				Window.draw(menu.textQuit);
			}
			Window.setView(view);
		}

		Window.setView(Window.getDefaultView());
		Window.display();
		Window.clear();
	}
}