#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Menu.h"
#include "Misc.h"
#include "Objects.h"
#include "Buildings.h"

#define GameName "Vulcania: Commencement"
sf::String Version = "0.1.1";
sf::Vector2f screenDimensions(800, 600);

Player player;
Menu menu;
Misc misc;
Objects objects;
Buildings buildings;

sf::Vector2i source(1, Misc::Direction::Up);

bool showObjectiveBox = true;
bool showSignBox;
std::string gameObjectiveCurrent = "None";

int currentObjective = 0;
int gamePart = 0;

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

int main()
{
	int backgroundCurrentFrame = 0;

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	float frameMenuCounter = 0, switchMenuFrame = 100, frameMenuSpeed = 1500;
	float framePedMovementCounter = 0, switchPedMovementFrame = 100, framePedMovementSpeed = 500;
	float frameFlashCounter = 0, switchFlashFrame = 100, frameFlashSpeed = 400;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode((int)screenDimensions.x, (int)screenDimensions.y), GameName, sf::Style::Titlebar | sf::Style::Close);

	Window.setFramerateLimit(60);
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
	sf::Texture signsTexture;
	sf::Texture boxesTexture;
	sf::Sprite arrow;
	sf::Sprite exclaim;
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
	if (misc.fastMode == false)
		moveSpeed = 100.0f;
	else if (misc.fastMode == true)
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
	if (!fontNoodle.loadFromFile("fonts/noodle.ttf")) { std::cout << "Error: Game failed to load 'noodle' font." << std::endl; }
	sf::Font fontViper;
	if (!fontViper.loadFromFile("fonts/viper.ttf")) { std::cout << "Error: Game failed to load 'viper' font." << std::endl; }
	sf::Font fontMain;
	if (!fontMain.loadFromFile("fonts/arial.ttf")) { std::cout << "Error: Game failed to load 'arial' font." << std::endl; }

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

	sf::Text textgameObjectiveCurrent(gameObjectiveCurrent, fontMain, 34);
	textgameObjectiveCurrent.setScale(0.29f, 0.29f);
	textgameObjectiveCurrent.setColor(sf::Color(255, 255, 255));
	textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);

	// Loading the map textures
	sf::Texture Building;
	sf::Texture Floor;
	sf::Texture Object;
	sf::Texture BoundaryV;
	sf::Texture BoundaryH;

	sf::Sprite Grass;
	loadFloor(Floor, Grass);

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
			else if (misc.gamestate == Misc::GameState::MainMenu)
			{
				menu.navigate();
				if (Event.type == sf::Event::KeyPressed)
				{
					if (Event.key.code == sf::Keyboard::Return)
					{
						if (menu.Option == menu.optionStartGame)
						{
							misc.gamestate = Misc::GameState::InGame;
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
			else if (misc.gamestate == Misc::GameState::InGame)
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
				source.y = Misc::Direction::Up;
				player.moving = true;
				if (player.getPosition().y >= 0)
					player.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				source.y = Misc::Direction::Down;
				player.moving = true;
				player.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				source.y = Misc::Direction::Right;
				player.moving = true;
				player.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				source.y = Misc::Direction::Left;
				player.moving = true;
				if (player.getPosition().x >= 0)
					player.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			}
		}

		if (misc.gamestate == Misc::GameState::InGame && misc.showTextBox == true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				misc.showTextBox = false;
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
			source.y = Misc::Direction::Right;
			player.frozen = true;
			showArrow = false;
			arrowFlash = false;
			showExclaim = true;
			if (pedMailman.getPosition().x >= player.getPosition().x + 26)
			{
				pedMailman.setTextureRect(sf::IntRect((int)pedSource * 32, (int)Misc::Direction::Left * 32, 32, 32));
				pedMailman.move(movePedSpeed * direction * clockPedMovement.getElapsedTime().asSeconds());
				pedSource++;
				if (pedSource * 32 >= pedMailmanTexture.getSize().x)
					pedSource = 0;
			}
			else
			{
				showExclaim = false;
				misc.showTextBox = true;
				gamePart = 2;
				Part = 0;
			}
		}
		else if (gamePart == 2)
		{
			player.frozen = true;
			if (Part == 0)
			{
				misc.textInTextBox = "MAILMAN: Do you live here? I have a package for this address.";
				misc.showTextBox = true;
			}
			else if (Part == 1)
			{
				misc.textInTextBox = "MAILMAN hands you the package.";
				misc.showTextBox = true;
			}
			else if (Part == 2)
			{
				misc.textInTextBox = "MAILMAN: Sign here with your name.";
				misc.showTextBox = true;
			}
			else if (Part == 3)
			{
				gameObjectiveCurrent = "Sign with your name.";
				showSignBox = true;
				misc.showTextBox = false;
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
			if (source.x * 32 >= (int)pTexture.getSize().x)
				source.x = 0;
		}

		framePedMovementCounter = (updatePedMovementFrame) ? framePedMovementCounter + framePedMovementSpeed * clockPedMovement.restart().asSeconds() : 0;
		if (framePedMovementCounter >= switchPedMovementFrame)
		{
			framePedMovementCounter = 0;
		}

		// Drawing the map textures
		drawFloor("Grass", Floor, Grass, 0, 0, 0, 50000, 50000);

		buildings.draw("Main House", Building, MainHouse, 0, 760, 420);
		buildings.draw("House0", Building, House0, 1, 928, 431);
		buildings.draw("House1", Building, House1, 2, 1072, 451);
		buildings.draw("House2", Building, House2, 3, 787, 637);
		buildings.draw("House3", Building, House3, 4, 884, 608);
		buildings.draw("House4", Building, House4, 5, 1027, 604);
		buildings.spawnDoors();

		objects.draw("Object0", Object, Object0, 0, 730, 475);

		drawBoundaryV("BoundaryV0", BoundaryV, BoundaryV0, 0, 0);
		drawBoundaryV("BoundaryV1", BoundaryV, BoundaryV1, 0, 991);
		drawBoundaryH("BoundaryH0", BoundaryH, BoundaryH0, 575, 0);
		drawBoundaryH("BoundaryH1", BoundaryH, BoundaryH1, 1150, 0);

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

		if (misc.gamestate == Misc::GameState::InGame)
		{
			position.x = player.getPosition().x;
			position.y = player.getPosition().y;
		}

		view.setCenter(position);

		Window.setView(view);

		player.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
		background.setTextureRect(sf::IntRect(0, backgroundCurrentFrame * 600, 800, 600));

		misc.drawInTextBox.setString(misc.textInTextBox);
		misc.drawInTextBox.setPosition((misc.textbox.getLocalBounds().width - misc.drawInTextBox.getGlobalBounds().width) / 2 + misc.textbox.getPosition().x, (misc.textbox.getLocalBounds().height - 2 * misc.drawInTextBox.getGlobalBounds().height) / 2 + misc.textbox.getPosition().y);
		textgameObjectiveCurrent.setString(gameObjectiveCurrent);
		textgameObjectiveCurrent.setPosition((objectivebox.getLocalBounds().width - textgameObjectiveCurrent.getGlobalBounds().width) / 2 + objectivebox.getPosition().x, (objectivebox.getLocalBounds().height - textgameObjectiveCurrent.getGlobalBounds().height) / 2 + objectivebox.getPosition().y);

		if (misc.gamestate == Misc::GameState::StartMenu)
		{
			Window.draw(textPressSpace);
			Window.draw(logo);
		}
		else if (misc.gamestate == Misc::GameState::MainMenu)
		{
			Window.draw(background);
			Window.draw(logoname);
			Window.draw(menu.textMenuVersion);
			Window.draw(menu.textNewGame);
			Window.draw(menu.textOptions);
			Window.draw(menu.textQuit);
		}
		else if (misc.gamestate == Misc::GameState::InGame)
		{
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
			if (misc.showTextBox == true)
			{
				Window.draw(misc.textbox);
				Window.draw(misc.drawInTextBox);
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