#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Menu.h"

#define GameName "Vulcania: Commencement"
sf::String Version = "0.1.1";

#define GameWidth  800
#define GameHeight 600

enum GameState { StartMenu, MainMenu, InGame };
enum Direction { Down, Left, Right, Up };

int gamestate = StartMenu;

Player player;
Menu menu;

sf::Vector2i source(1, Up);

bool lockMode = true;
bool fastMode = false;

bool showTextBox = false;
bool showObjectiveBox = true;
bool showSignBox;
std::string textInTextBox = "";
std::string gameObjectiveCurrent = "None";

int currentObjective = 0;
int gamePart = 0;

void solidObject(std::string objectName, float left, float right, float top, float bottom)
{
	if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
		player.setPosition(player.prevPos.x, player.prevPos.y);
}

void loadBuilding(sf::Texture& buildingsTexture, sf::Sprite& buildings)
{
	if (!buildingsTexture.loadFromFile("images/map/buildings.png")) { std::cout << "Error: Game failed to load 'buildings' image." << std::endl; }
	buildings.setTexture(buildingsTexture);
}

void drawBuilding(std::string buildingName, sf::Texture& buildingsTexture, sf::Sprite& buildings, int buildingNumber, float objectX, float objectY)
{
	if (buildingNumber == 0)
	{
		buildings.setTextureRect(sf::IntRect(0, 0, 140, 122));
	}
	else if (buildingNumber == 1)
	{
		buildings.setTextureRect(sf::IntRect(158, 0, 116, 114));
	}
	else if (buildingNumber == 2)
	{
		buildings.setTextureRect(sf::IntRect(298, 0, 80, 97));
	}
	else if (buildingNumber == 3)
	{
		buildings.setTextureRect(sf::IntRect(401, 0, 61, 65));
	}
	else if (buildingNumber == 4)
	{
		buildings.setTextureRect(sf::IntRect(482, 0, 108, 93));
	}
	else if (buildingNumber == 5)
	{
		buildings.setTextureRect(sf::IntRect(612, 0, 124, 98));
	}
	if (buildingNumber >= 0 && buildingNumber <= 5)
	{
		buildings.setPosition(objectX, objectY);
		float left = buildings.getGlobalBounds().left - 24;
		float right = left + buildings.getGlobalBounds().width + 16;
		float top = buildings.getGlobalBounds().top - 32;
		float bottom = top + buildings.getGlobalBounds().height;
		if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
			player.setPosition(player.prevPos.x, player.prevPos.y);
	}
	else
		std::cout << "Error: '" << buildingName << "' has failed to load. (invalid building number)." << std::endl;
}

void loadObject(sf::Texture& objectsTexture, sf::Sprite& object)
{
	if (!objectsTexture.loadFromFile("images/map/misc.png")) { std::cout << "Error: Game failed to load 'misc' image." << std::endl; }
	object.setTexture(objectsTexture);
}

void drawObject(std::string objectName, sf::Texture& objectsTexture, sf::Sprite& objects, int objectNumber, float objectX, float objectY)
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
	if (objectNumber >= 0 && objectNumber <= 2)
	{
		objects.setPosition(objectX, objectY);
		float left = objects.getGlobalBounds().left - 24;
		float right = left + objects.getGlobalBounds().width + 16;
		float top = objects.getGlobalBounds().top - 32;
		float bottom = top + objects.getGlobalBounds().height;
		if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
			player.setPosition(player.prevPos.x, player.prevPos.y);
	}
	else
		std::cout << "Error: '" << objectName << "' has failed to load. (invalid object number)." << std::endl;
}

void loadFloor(sf::Texture& floorsTexture, sf::Sprite& floors)
{
	if (!floorsTexture.loadFromFile("images/map/floor.png")) { std::cout << "Error: Game failed to load 'floor' image." << std::endl; }
	floorsTexture.setRepeated(true);
	floors.setTextureRect(sf::IntRect(0, 0, 64, 64));
	floors.setTexture(floorsTexture);
}

void drawFloor(std::string floorName, sf::Texture& floorsTexture, sf::Sprite& floors, int floorNumber, float floorX, float floorY, int floorW, int floorH)
{
	if (floorNumber == 0)
	{
		floors.setTextureRect(sf::IntRect(0, 0, floorW, floorH));
		floors.setPosition(floorX, floorY);
	}
	else
	{
		std::cout << "Floor: '" << floorName << "' has failed to load. (invalid floor number)." << std::endl;
	}
}

void loadBoundaryV(sf::Texture& boundaryVTexture, sf::Sprite& boundaryV)
{
	if (!boundaryVTexture.loadFromFile("images/map/treeboundvert.png")) { std::cout << "Error: Game failed to load 'treeboundvert' image." << std::endl; }
	boundaryV.setTexture(boundaryVTexture);
}

void drawBoundaryV(std::string boundaryVName, sf::Texture& boundaryVTexture, sf::Sprite& boundaryV, float boundaryX, float boundaryY)
{
	boundaryV.setPosition(boundaryX, boundaryY);
	float left = boundaryV.getGlobalBounds().left - 24;
	float right = left + boundaryV.getGlobalBounds().width + 16;
	float top = boundaryV.getGlobalBounds().top - 32;
	float bottom = top + boundaryV.getGlobalBounds().height;
	if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
		player.setPosition(player.prevPos.x, player.prevPos.y);
}

void loadBoundaryH(sf::Texture& boundaryHTexture, sf::Sprite& boundaryH)
{
	if (!boundaryHTexture.loadFromFile("images/map/treeboundhoriz.png")) { std::cout << "Error: Game failed to load 'treeboundhoriz' image." << std::endl; }
	boundaryH.setTexture(boundaryHTexture);
}

void drawBoundaryH(std::string boundaryHName, sf::Texture& boundaryHTexture, sf::Sprite& boundaryH, float boundaryX, float boundaryY)
{
	boundaryH.setPosition(boundaryX, boundaryY);
	float left = boundaryH.getGlobalBounds().left - 24;
	float right = left + boundaryH.getGlobalBounds().width + 16;
	float top = boundaryH.getGlobalBounds().top - 32;
	float bottom = top + boundaryH.getGlobalBounds().height;
	if (player.getPosition().x > left && player.getPosition().x < right && player.getPosition().y > top && player.getPosition().y < bottom)
		player.setPosition(player.prevPos.x, player.prevPos.y);
}

void door(std::string doorName, float doorX, float doorY)
{
	sf::Vector2f newDoor(doorX, doorY);
	float doorRadius = 10;
	if (player.getPosition().x >= doorX - doorRadius && player.getPosition().x <= doorX + doorRadius && player.getPosition().y >= doorY && player.getPosition().y <= doorY + 0.5)
	{
		if (gamestate == InGame && player.moving == true && source.y == Up && player.enteredDoor == false)
		{
			if (lockMode == false)
			{
				std::cout << "Player has entered '" + doorName + "' door." << std::endl;
				player.enteredDoor = true;
			}
			else if (lockMode == true)
			{
				std::cout << "Player has tried to enter '" + doorName + "' door. (lockMode)" << std::endl;
				showTextBox = true;
				player.frozen = true;
				textInTextBox = "Perhaps I should complete the task at hand first.";
			}
		}
	}
}

int main()
{
	int backgroundCurrentFrame = 0;

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	float frameMenuCounter = 0, switchMenuFrame = 100, frameMenuSpeed = 1500;
	float framePedMovementCounter = 0, switchPedMovementFrame = 100, framePedMovementSpeed = 500;
	float frameFlashCounter = 0, switchFlashFrame = 100, frameFlashSpeed = 400;

	sf::Vector2f screenDimensions(GameWidth, GameHeight);
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), GameName, sf::Style::Titlebar | sf::Style::Close);

	Window.setKeyRepeatEnabled(false);

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
	sf::Texture boxesTexture;
	sf::Texture signsTexture;
	sf::Sprite arrow;
	sf::Sprite exclaim;
	sf::Sprite textbox;
	sf::Sprite objectivebox;
	sf::Sprite signbox;

	sf::Texture pedMailmanTexture;
	sf::Sprite pedMailman;

	sf::Clock clock;
	sf::Clock clockMenu;
	sf::Clock clockFlash;
	sf::Clock clockPedMovement;
	sf::Clock totalGameTime;

	float moveSpeed;
	if (fastMode == false)
		moveSpeed = 100.0f;
	else if (fastMode == true)
		moveSpeed = 500.0f;

	float movePedSpeed = 0.35f;

	sf::View view;

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

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

	if (!pedMailmanTexture.loadFromFile("images/peds/Mailman.png")) { std::cout << "Error: Game failed to load 'mailman' image." << std::endl; }

	sf::Font fontNoodle;
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "Error: Game failed to load 'big_noodle_titling' font." << std::endl; }
	sf::Font fontViper;
	if (!fontViper.loadFromFile("fonts/viper.ttf")) { std::cout << "Error: Game failed to load 'viper' font." << std::endl; }
	sf::Font fontMain;
	if (!fontMain.loadFromFile("fonts/arial.ttf")) { std::cout << "Error: Game failed to load 'lucon' font." << std::endl; }

	player.setTexture(pTexture);
	player.setPosition(713, 973);

	map.setTexture(mTexture);

	background.setTexture(bTexture);

	logo.setTexture(lTexture);
	logo.setPosition(260, 70);

	logoname.setTexture(lnTexture);
	logoname.setPosition(92, 100);

	bool arrowFlash = false;
	bool showArrow = false;
	arrow.setTexture(signsTexture);
	arrow.setTextureRect(sf::IntRect(0, 0, 10, 18));
	arrow.setPosition(852, 515);
	arrow.setRotation(180);

	bool showExclaim = false;
	exclaim.setTexture(signsTexture);
	exclaim.setTextureRect(sf::IntRect(15, 0, 20, 20));

	textbox.setTexture(boxesTexture);
	textbox.setTextureRect(sf::IntRect(200, 0, 500, 146));
	textbox.setPosition((screenDimensions.x - textbox.getGlobalBounds().width) / 2, 444);

	objectivebox.setTexture(boxesTexture);
	objectivebox.setTextureRect(sf::IntRect(0, 0, 200, 81));
	objectivebox.setPosition(3, 3);

	signbox.setTexture(boxesTexture);
	signbox.setTextureRect(sf::IntRect(0, 147, 331, 488));
	signbox.setPosition((screenDimensions.x - signbox.getGlobalBounds().width) / 2, (screenDimensions.y - signbox.getGlobalBounds().height) / 2);

	pedMailman.setTexture(pedMailmanTexture);

	sf::String startingPressSpace = "Press space to start game.";
	sf::Text textPressSpace(startingPressSpace, fontNoodle, 20);
	textPressSpace.setColor(sf::Color(255, 255, 255));
	textPressSpace.setPosition(320, 535);

	menu.draw();

	sf::Text drawInTextBox(textInTextBox, fontMain, 12);
	drawInTextBox.setColor(sf::Color(255, 255, 255));
	drawInTextBox.setPosition((textbox.getLocalBounds().width - drawInTextBox.getLocalBounds().width) / 2 + textbox.getPosition().x, (textbox.getLocalBounds().height - 2 * drawInTextBox.getLocalBounds().height) / 2 + textbox.getPosition().y);

	sf::String gameObjective = "Main Objective:";
	sf::Text textGameObjective(gameObjective, fontMain, 10);
	textGameObjective.setColor(sf::Color(255, 255, 255));
	textGameObjective.setPosition((objectivebox.getLocalBounds().width - textGameObjective.getLocalBounds().width) / 2 + objectivebox.getPosition().x, 7);

	sf::Text textgameObjectiveCurrent(gameObjectiveCurrent, fontMain, 10);
	textgameObjectiveCurrent.setColor(sf::Color(255, 255, 255));
	textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getLocalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getLocalBounds().height) / 2 + objectivebox.getPosition().y);

	// Loading the map textures
	sf::Texture Building;
	sf::Texture Floor;
	sf::Texture Object;
	sf::Texture BoundaryV;
	sf::Texture BoundaryH;

	sf::Sprite Grass;
	loadFloor(Floor, Grass);

	sf::Sprite MainHouse;
	loadBuilding(Building, MainHouse);
	sf::Sprite House0;
	loadBuilding(Building, House0);
	sf::Sprite House1;
	loadBuilding(Building, House1);
	sf::Sprite House2;
	loadBuilding(Building, House2);
	sf::Sprite House3;
	loadBuilding(Building, House3);
	sf::Sprite House4;
	loadBuilding(Building, House4);

	sf::Sprite Object0;
	loadObject(Object, Object0);

	sf::Sprite BoundaryV0;
	loadBoundaryV(BoundaryV, BoundaryV0);
	sf::Sprite BoundaryV1;
	loadBoundaryV(BoundaryV, BoundaryV1);
	sf::Sprite BoundaryH0;
	loadBoundaryH(BoundaryH, BoundaryH0);
	sf::Sprite BoundaryH1;
	loadBoundaryH(BoundaryH, BoundaryH1);

	sf::Vector2f direction;
	float pedSource;
	int Part = 0;

	sf::Text text("", fontMain, 30);
	text.setColor(sf::Color(0, 0, 0));
	sf::String sentence;

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			if (gamestate == StartMenu)
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Space)
					{
						gamestate = MainMenu;
						menu.textNewGame.setColor(sf::Color(204, 204, 0));
					}
				}
			}
			else if (gamestate == MainMenu)
			{
				menu.navigate();
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Return)
					{
						if (menu.Option == menu.optionStartGame)
						{
							gamestate = InGame;
							updateMenuFrame = false;
							if (!SavedGameExists)
							{
								std::ofstream file(saveFileName);
							}
							if (gamePart == 0)
							{
								showArrow = true;
								arrowFlash = true;
							}
						}
						else if (menu.Option == menu.optionQuit)
						{
							Window.close();
							std::cout << "Test.\n\n";
						}
					}
				}
			}
			else if (gamestate == InGame)
			{
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::X)
					{
						std::cout << "PlayerX: " << player.getPosition().x << " PlayerY: " << player.getPosition().y << " player.moving: " << player.moving << std::endl;
						std::cout << "GamePart: " << gamePart << " player.frozen: " << player.frozen << std::endl;
					}
					else if (Event.key.code == sf::Keyboard::Space)
					{
						if (gamePart == 2 && Part >= 0 && Part <= 2)
						{
							Part += 1;
						}
					}
					else if (Event.key.code == sf::Keyboard::Return)
					{
						if (gamePart == 2 && Part == 3)
						{
							std::cout << "Game has saved information into the game save file." << std::endl;
							showSignBox = false;
							player.frozen = false;
							gamePart = 3;
						}
					}
				}
				else if (Event.type == sf::Event::TextEntered)
				{
					if (gamePart == 2 && Part == 3)
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
				*//*
				case sf::Event::MouseMoved:
				std::cout << "X: " << Event.mouseMove.x << " Y: " << Event.mouseMove.y << std::endl;
				std::cout << "Total Game Time: " << totalGameTime.getElapsedTime().asSeconds() << std::endl;
				std::cout << "Menu Option: " << menuOption << std::endl;
				std::cout << "Left: " << logo.getGlobalBounds().left << " Right: " << logo.getGlobalBounds().left + logo.getGlobalBounds().width << " Top: " << logo.getGlobalBounds().top << " Bottom: " << logo.getGlobalBounds().top + logo.getGlobalBounds().height << std::endl;
				*/
			}
		}

		player.prevPos.x = player.getPosition().x;
		player.prevPos.y = player.getPosition().y;

		if (gamestate == InGame && player.frozen == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				player.running = true;
				moveSpeed = 200.0f;
				frameSpeed = 10000;
			}
			else
			{
				player.running = false;
				moveSpeed = 100.0f;
				frameSpeed = 500;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				source.y = Up;
				player.moving = true;
				if (player.getPosition().y >= 0)
					player.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				source.y = Down;
				player.moving = true;
				player.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				source.y = Right;
				player.moving = true;
				player.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				source.y = Left;
				player.moving = true;
				if (player.getPosition().x >= 0)
					player.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
		}

		if (gamestate == InGame && showTextBox == true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				showTextBox = false;
				player.frozen = false;
			}
		}

		if (gamePart == 0)
		{
			gameObjectiveCurrent = "Go home.";
			if (player.getPosition().x >= 820 && player.getPosition().x <= 851 && player.getPosition().y >= 510 && player.getPosition().y <= 538)
			{
				gamePart = 1;
				pedMailman.setPosition(1114, player.getPosition().y);
				direction = player.getPosition() - pedMailman.getPosition();
				pedSource = 0;
			}
		}
		else if (gamePart == 1)
		{
			source.y = Right;
			player.frozen = true;
			showArrow = false;
			arrowFlash = false;
			showExclaim = true;
			if (pedMailman.getPosition().x >= player.getPosition().x + 26)
			{
				pedMailman.setTextureRect(sf::IntRect(pedSource * 32, Left * 32, 32, 32));
				pedMailman.move(movePedSpeed * direction * clockPedMovement.getElapsedTime().asSeconds());
				pedSource++;
				if (pedSource * 32 >= pedMailmanTexture.getSize().x)
					pedSource = 0;
			}
			else
			{
				showExclaim = false;
				showTextBox = true;
				gamePart = 2;
				Part = 0;
			}
		}
		else if (gamePart == 2)
		{
			player.frozen = true;
			if (Part == 0)
			{
				textInTextBox = "MAILMAN: Do you live here? I have a package for this address.";
				showTextBox = true;
			}
			else if (Part == 1)
			{
				textInTextBox = "MAILMAN hands you the package.";
				showTextBox = true;
			}
			else if (Part == 2)
			{
				textInTextBox = "MAILMAN: Sign here with your name.";
				showTextBox = true;
			}
			else if (Part == 3)
			{
				gameObjectiveCurrent = "Sign with your name.";
				showSignBox = true;
				showTextBox = false;
			}
		}
		else
		{
			gameObjectiveCurrent = "None.";
		}

		frameCounter = (updateFrame) ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;
		if (frameCounter >= switchFrame && player.moving == true)
		{
			frameCounter = 0;
			source.x++;
			if (source.x * 32 >= pTexture.getSize().x)
				source.x = 0;
		}

		framePedMovementCounter = (updatePedMovementFrame) ? framePedMovementCounter + framePedMovementSpeed * clockPedMovement.restart().asSeconds() : 0;
		if (framePedMovementCounter >= switchPedMovementFrame)
		{
			framePedMovementCounter = 0;
		}

		// Drawing the map textures
		drawFloor("Grass", Floor, Grass, 0, 0, 0, 50000, 50000);

		drawBuilding("Main House", Building, MainHouse, 0, 760, 420);
		drawBuilding("House0", Building, House0, 1, 928, 431);
		drawBuilding("House1", Building, House1, 2, 1072, 451);
		drawBuilding("House2", Building, House2, 3, 787, 637);
		drawBuilding("House3", Building, House3, 4, 884, 608);
		drawBuilding("House4", Building, House4, 5, 1027, 604);

		drawObject("Object0", Object, Object0, 0, 730, 475);

		drawBoundaryV("BoundaryV0", BoundaryV, BoundaryV0, 0, 0);
		drawBoundaryV("BoundaryV1", BoundaryV, BoundaryV1, 0, 991);
		drawBoundaryH("BoundaryH0", BoundaryH, BoundaryH0, 575, 0);
		drawBoundaryH("BoundaryH1", BoundaryH, BoundaryH1, 1150, 0);

		door("Main House", 827, 510);
		door("House 0", 960, 514);
		door("House 1", 1082, 516);
		door("House 2", 793, 670);
		door("House 3", 895, 669);
		door("House 4", 1072, 670);

		player.moving = false;

		frameFlashCounter = (updateFlashFrame) ? frameFlashCounter + frameFlashSpeed * clockFlash.restart().asSeconds() : 0;
		if (frameFlashCounter >= switchFlashFrame && showArrow == true)
		{
			frameFlashCounter = 0;
			if (arrowFlash == true)
				arrowFlash = false;
			else
				arrowFlash = true;
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

		if (gamestate == InGame)
		{
			position.x = player.getPosition().x;
			position.y = player.getPosition().y;
		}

		view.setCenter(position);

		Window.setView(view);

		player.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
		background.setTextureRect(sf::IntRect(0, backgroundCurrentFrame * 600, 800, 600));

		drawInTextBox.setString(textInTextBox);
		drawInTextBox.setPosition((textbox.getLocalBounds().width - drawInTextBox.getLocalBounds().width) / 2 + textbox.getPosition().x, (textbox.getLocalBounds().height - 2 * drawInTextBox.getLocalBounds().height) / 2 + textbox.getPosition().y);
		textgameObjectiveCurrent.setString(gameObjectiveCurrent);
		textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getLocalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getLocalBounds().height) / 2 + objectivebox.getPosition().y);

		if (gamestate == StartMenu)
		{
			Window.draw(textPressSpace);
			Window.draw(logo);
		}
		else if (gamestate == MainMenu)
		{
			Window.draw(background);
			Window.draw(logoname);
			Window.draw(menu.textMenuVersion);
			Window.draw(menu.textNewGame);
			//Window.draw(textContinueGame);
			Window.draw(menu.textOptions);
			Window.draw(menu.textQuit);
		}
		else if (gamestate == InGame)
		{
			//Window.draw(map);
			Window.draw(Grass);
			Window.draw(BoundaryV0);
			Window.draw(BoundaryV1);
			Window.draw(BoundaryH0);
			Window.draw(BoundaryH1);
			Window.draw(MainHouse);
			Window.draw(House0);
			Window.draw(House1);
			Window.draw(House2);
			Window.draw(House3);
			Window.draw(House4);
			Window.draw(Object0);
			if (gamePart >= 1 && gamePart <= 2)
			{
				Window.draw(pedMailman);
			}
			Window.draw(player);
			if (arrowFlash == true && showArrow == true)
			{
				Window.draw(arrow);
			}
			if (showExclaim == true)
			{
				exclaim.setPosition(player.getPosition().x + 8, player.getPosition().y - 25);
				Window.draw(exclaim);
			}
			Window.setView(Window.getDefaultView());
			if (showTextBox == true)
			{
				Window.draw(textbox);
				Window.draw(drawInTextBox);
			}
			if (showObjectiveBox == true)
			{
				Window.draw(objectivebox);
				Window.draw(textGameObjective);
				if (currentObjective == 0)
					Window.draw(textgameObjectiveCurrent);
			}
			if (showSignBox == true)
			{
				Window.draw(signbox);
				Window.draw(text);
			}
			Window.setView(view);
		}

		Window.setView(Window.getDefaultView());
		Window.display();
		Window.clear();
	}
}