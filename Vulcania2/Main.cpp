#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "Menu.h"
#include "Misc.h"
#include "Objects.h"
#include "Buildings.h"
#include "Objective.h"
#include "Ped.h"

Misc misc;
Menu menu;
Player player;
Objects objects;
Buildings buildings;
Objective objective;

Ped courier;

void loadingScreen(sf::RenderWindow &Window)
{
	sf::Font fontNoodle;
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "Error: Game failed to load 'noodle' font." << std::endl; }
	sf::Text textLoading("Loading...", fontNoodle, 20);
	textLoading.setPosition((misc.screenDimensions.x - textLoading.getGlobalBounds().width) / 2, 535);
	Window.draw(textLoading);
	Window.display();
}

int main()
{
	int backgroundCurrentFrame = 0;

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	float frameMenuCounter = 0, switchMenuFrame = 100, frameMenuSpeed = 1500;
	float framePedMovementCounter = 0, switchPedMovementFrame = 100, framePedMovementSpeed = 500;
	float frameFlashCounter = 0, switchFlashFrame = 100, frameFlashSpeed = 400;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode((int)misc.screenDimensions.x, (int)misc.screenDimensions.y), "Vulcania: Commencement", sf::Style::Titlebar | sf::Style::Close);
	Window.setFramerateLimit(100);
	Window.setKeyRepeatEnabled(false);

	sf::Thread loadingThread(loadingScreen, std::ref(Window));
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

	sf::Clock clock;
	sf::Clock clockMenu;
	sf::Clock clockFlash;
	sf::Clock totalGameTime;

	float moveSpeed;
	if (misc.fastMode == false)
		moveSpeed = 100.0f;
	else if (misc.fastMode == true)
		moveSpeed = 500.0f;

	sf::View view;

	view.reset(sf::FloatRect(0, 0, misc.screenDimensions.x, misc.screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	bool updateFrame = true;
	bool updateMenuFrame = true;
	bool updatePedMovementFrame = true;
	bool updateFlashFrame = true;

	if (!pTexture.loadFromFile("images/peds/Player.png")) { std::cout << "Error: Game failed to load 'player' image." << std::endl; }
	if (!mTexture.loadFromFile("images/map/Map.png")) { std::cout << "Error: Game failed to load 'map' image." << std::endl; }
	if (!bTexture.loadFromFile("images/misc/Background.png")) { std::cout << "Error: Game failed to load 'background' image." << std::endl; }
	if (!lTexture.loadFromFile("images/misc/Logo.png")) { std::cout << "Error: Game failed to load 'logo' image." << std::endl; }
	if (!lnTexture.loadFromFile("images/misc/Logoname.png")) { std::cout << "Error: Game failed to load 'logoname' image." << std::endl; }
	if (!signsTexture.loadFromFile("images/misc/signs.png")) { std::cout << "Error: Game failed to load 'signs' image." << std::endl; }
	if (!boxesTexture.loadFromFile("images/boxes/boxes.png")) { std::cout << "Error: Game failed to load 'boxes' image." << std::endl; }

	if (!pedCourierTexture.loadFromFile("images/peds/Courier.png")) { std::cout << "Error: Game failed to load 'courier' image." << std::endl; }

	sf::Font fontNoodle;
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "Error: Game failed to load 'noodle' font." << std::endl; }
	sf::Font fontViper;
	if (!fontViper.loadFromFile("fonts/viper.ttf")) { std::cout << "Error: Game failed to load 'viper' font." << std::endl; }
	sf::Font fontMain;
	if (!fontMain.loadFromFile("fonts/arial.ttf")) { std::cout << "Error: Game failed to load 'arial' font." << std::endl; }

	player.setTexture(pTexture);
	player.setPosition(605, 1255);

	map.setTexture(mTexture);

	background.setTexture(bTexture);

	logo.setTexture(lTexture);
	logo.setPosition(260, 70);

	logoname.setTexture(lnTexture);
	logoname.setPosition(92, 100);

	arrow.setTexture(signsTexture);
	arrow.setTextureRect(sf::IntRect(0, 0, 10, 18));
	arrow.setPosition(852, 515);
	arrow.setRotation(180);

	exclaim.setTexture(signsTexture);
	exclaim.setTextureRect(sf::IntRect(15, 0, 20, 20));

	objectivebox.setTexture(boxesTexture);
	objectivebox.setTextureRect(sf::IntRect(0, 0, 200, 81));
	objectivebox.setPosition(3, 3);

	signbox.setTexture(boxesTexture);
	signbox.setTextureRect(sf::IntRect(0, 147, 331, 488));
	signbox.setPosition((misc.screenDimensions.x - signbox.getGlobalBounds().width) / 2, (misc.screenDimensions.y - signbox.getGlobalBounds().height) / 2);

	courier.setTexture(pedCourierTexture);

	sf::String startingPressSpace = "Press space to start game.";
	sf::Text textPressSpace(startingPressSpace, fontNoodle, 20);
	textPressSpace.setColor(sf::Color(255, 255, 255));
	textPressSpace.setPosition((misc.screenDimensions.x - textPressSpace.getGlobalBounds().width) / 2, 535);

	menu.draw();
	menu.textNewGame.setFont(fontNoodle);
	menu.textContinueGame.setFont(fontNoodle);
	menu.textOptions.setFont(fontNoodle);
	menu.textQuit.setFont(fontNoodle);
	menu.textMenuVersion.setFont(fontNoodle);

	misc.loadTextBox();
	misc.textbox.setTexture(boxesTexture);
	misc.drawInTextBox.setFont(fontMain);

	sf::String gameObjective = "Main Objective:";
	sf::Text textGameObjective(gameObjective, fontMain, 34);
	textGameObjective.setScale(0.29f, 0.29f);
	textGameObjective.setStyle(sf::Text::Bold);
	textGameObjective.setColor(sf::Color(255, 255, 255));
	textGameObjective.setPosition((objectivebox.getLocalBounds().width - textGameObjective.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, 7);

	sf::Text textgameObjectiveCurrent(objective.objCurrentText, fontMain, 34);
	textgameObjectiveCurrent.setScale(0.29f, 0.29f);
	textgameObjectiveCurrent.setColor(sf::Color(255, 255, 255));
	textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);

	// Loading the map textures
	sf::Texture Building;
	sf::Texture Floor;
	sf::Texture Background;
	sf::Texture Object;
	sf::Texture BoundaryV;
	sf::Texture BoundaryH;

	sf::Sprite Grass;
	misc.loadFloor(Floor, Grass);

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

	sf::Text text("", fontMain, 30);
	text.setColor(sf::Color(0, 0, 0));
	sf::String sentence;

	loadingThread.terminate();
	std::cout << "*** Loading Time: " << totalGameTime.getElapsedTime().asSeconds() + 0.3 << " seconds." << std::endl;

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
								Window.close();
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
					if (Event.key.code == sf::Keyboard::X)
					{
						std::cout << "Position: (" << player.getPosition().x << ", " << player.getPosition().y << ") | player.moving: " << player.moving << " | player.frozen: " << player.frozen << std::endl;
						std::cout << "objective.currentObj: " << objective.currentObj << " | objective.part: " << objective.part << std::endl;
					}
					else if (Event.key.code == sf::Keyboard::P || Event.key.code == sf::Keyboard::Escape)
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
						if (objective.part == 2 && objective.subPart >= 0 && objective.subPart <= 2)
						{
							objective.subPart += 1;
						}
					}
					else if (Event.key.code == sf::Keyboard::Return)
					{
						if (objective.part == 2 && objective.subPart == 3)
						{
							std::cout << "Game has saved information into the game save file." << std::endl;
							misc.showSignBox = false;
							player.frozen = false;
							objective.part = 3;
						}
					}
				}
				else if (Event.type == sf::Event::TextEntered)
				{
					if (objective.part == 2 && objective.subPart == 3)
					{
						if (Event.text.unicode >= 32 && Event.text.unicode <= 126 && sentence.getSize() <= 14)
							sentence += (char)Event.text.unicode;
						else if (Event.text.unicode == 8 && sentence.getSize() > 0)
							sentence.erase(sentence.getSize() - 1, sentence.getSize());

						text.setString(sentence);
						text.setPosition(300, 475);
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

		if (misc.gamestate == Misc::GameState::InGame && player.frozen == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				player.running = true;
				moveSpeed = 200.0f;
				frameSpeed = 1000;
			}
			else
			{
				player.running = false;
				if (misc.fastMode == false) { moveSpeed = 100.0f; }
				else { moveSpeed = 500.0f; }
				frameSpeed = 500;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				misc.source.y = Misc::Direction::Up;
				player.moving = true;
				if (player.getPosition().y >= 0)
					player.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				misc.source.y = Misc::Direction::Down;
				player.moving = true;
				player.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				misc.source.y = Misc::Direction::Right;
				player.moving = true;
				player.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				misc.source.y = Misc::Direction::Left;
				player.moving = true;
				if (player.getPosition().x >= 0)
					player.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
		}

		if (misc.gamestate == Misc::GameState::InGame && misc.showTextBox == true && misc.paused == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				misc.showTextBox = false;
				player.frozen = false;
			}
		}

		objective.initiate();

		frameCounter = (updateFrame) ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;
		if (frameCounter >= switchFrame && player.moving == true)
		{
			frameCounter = 0;
			misc.source.x++;
			if (misc.source.x * 32 >= (int)pTexture.getSize().x)
				misc.source.x = 0;
		}

		framePedMovementCounter = (updatePedMovementFrame) ? framePedMovementCounter + framePedMovementSpeed * courier.clockMovement.restart().asSeconds() : 0;
		if (framePedMovementCounter >= switchPedMovementFrame)
		{
			framePedMovementCounter = 0;
		}

		// Drawing the map textures
		misc.drawFloor("Grass", Floor, Grass, 0, 0, 0, 50000, 50000);

		misc.drawBackground("Grey", Background, Grey, 0, 0, 0, misc.screenDimensions.x, misc.screenDimensions.y);

		buildings.draw("Main House", Building, MainHouse, 0, 760, 420);
		buildings.draw("House0", Building, House0, 1, 928, 431);
		buildings.draw("House1", Building, House1, 2, 1072, 451);
		buildings.draw("House2", Building, House2, 3, 787, 637);
		buildings.draw("House3", Building, House3, 4, 884, 608);
		buildings.draw("House4", Building, House4, 5, 1027, 604);
		buildings.spawnDoors();

		objects.draw("Tree0", Object, Object0, 0, 730, 475);
		objects.draw("Tree1", Object, Object4, 0, 2224, 1688);
		objects.draw("Tree2", Object, Object5, 0, 2334, 1688);
		objects.draw("Tree2", Object, Object6, 0, 2444, 1688);
		objects.draw("Tree3", Object, Object7, 0, 2554, 1688);
		objects.draw("DeadUncle", Object, Object1, 3, 2540, 1796);
		objects.draw("Bush0", Object, Object2, 4, 2176, 1721);
		objects.draw("Bush1", Object, Object3, 4, 2340, 1721);

		misc.drawBoundaryV("BoundaryV0", BoundaryV, BoundaryV0, 0, 0);
		misc.drawBoundaryV("BoundaryV1", BoundaryV, BoundaryV1, 0, 1000);
		misc.drawBoundaryV("BoundaryV2", BoundaryV, BoundaryV2, 2080, 1870);
		misc.drawBoundaryV("BoundaryV3", BoundaryV, BoundaryV3, 2655, 1690);
		misc.drawBoundaryH("BoundaryH0", BoundaryH, BoundaryH0, 575, 0);
		misc.drawBoundaryH("BoundaryH1", BoundaryH, BoundaryH1, 1150, 0);
		misc.drawBoundaryH("BoundaryH2", BoundaryH, BoundaryH2, 700, 1123);
		misc.drawBoundaryH("BoundaryH3", BoundaryH, BoundaryH3, 700, 1700);
		misc.drawBoundaryH("BoundaryH4", BoundaryH, BoundaryH4, 1275, 1123);
		misc.drawBoundaryH("BoundaryH5", BoundaryH, BoundaryH5, 1275, 1700);
		misc.drawBoundaryH("BoundaryH6", BoundaryH, BoundaryH6, 2080, 1123);

		player.moving = false;

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

		player.setTextureRect(sf::IntRect(misc.source.x * 32, misc.source.y * 32, 32, 32));
		background.setTextureRect(sf::IntRect(0, backgroundCurrentFrame * 600, (int)misc.screenDimensions.x, (int)misc.screenDimensions.y));

		misc.drawInTextBox.setString(misc.textInTextBox);
		misc.drawInTextBox.setPosition((misc.textbox.getLocalBounds().width - misc.drawInTextBox.getGlobalBounds().width) / 2 + misc.textbox.getPosition().x, (misc.textbox.getLocalBounds().height - 2 * misc.drawInTextBox.getGlobalBounds().height) / 2 + misc.textbox.getPosition().y);
		textgameObjectiveCurrent.setString(objective.objCurrentText);
		textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);

		if (misc.gamestate == Misc::GameState::StartMenu)
		{
			Window.draw(textPressSpace);
			Window.draw(logo);
		}
		else if (misc.gamestate == Misc::GameState::MainMenu)
		{
			Window.setView(Window.getDefaultView());
			Window.draw(background);
			Window.draw(logoname);
			Window.draw(menu.textMenuVersion);
			if (objective.part == 0)
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
			Window.draw(Object1);
			Window.draw(Object2);
			Window.draw(Object3);
			Window.draw(Object4);
			Window.draw(Object5);
			Window.draw(Object6);
			Window.draw(Object7);
			if (objective.part >= 1 && objective.part <= 2) { Window.draw(courier); }
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
				Window.draw(misc.textbox);
				Window.draw(misc.drawInTextBox);
			}
			if (misc.showObjectiveBox == true)
			{
				Window.draw(objectivebox);
				Window.draw(textGameObjective);
				if (objective.currentObj >= 0) { Window.draw(textgameObjectiveCurrent); }
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