#include "Game.h"

Game::GameState Game::gameState;
using namespace std;
#include <iostream>
sf::RenderWindow Game::gameWindow;
sf::View Game::camera;

const int width = 800;
const int height = 600;

clock_t Game::t;

Player Game::player("res/bestbeaverisgodbeaver.png");

Map Game::map;
std::vector<int> mine;

//Temp//

sf::Texture bgTexture;
sf::Sprite bgSprite;

Level level(&Game::player);

////////

int Game::Init() {
	gameState = Uninitialized;

	gameWindow.create(sf::VideoMode(width, height), "Dam It Mr Beaver");
	gameWindow.setFramerateLimit(60);
	camera.setSize(width, height);
	camera.setCenter(width / 2, height / 2);
	camera.zoom(2.5);
	gameState = Paused;

	//Temp//

	bgTexture.loadFromFile("res/background.png");
	bgSprite.setTexture(bgTexture);
	
	level.load(Level::FOREST);

	////////

	return 0;
}

void Game::Start() {
	gameState = Running;

	while (gameState != Exiting) {
		Update();
	}
}

void Game::Update() {
	
	float dt = ((float)(clock() - t)) / CLOCKS_PER_SEC;
	t = clock();
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			gameWindow.close();
			gameState = Exiting;
		}
	}
	float speed = 500;
	

	//Player Input
	sf::Vector2f velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		
		velocity.y -= speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		velocity.x -= speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		velocity.y += speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		velocity.x += speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		sf::Vector2<int> tileAbovePlayer = player.findIntegerPlayerPosition(player.getPosition()); 
		tileAbovePlayer.y--;
		if (tileAbovePlayer.x >= 0 && tileAbovePlayer.y >= 0) {
			if (map.Tiles.at({ tileAbovePlayer.x, tileAbovePlayer.y })->tyleType == Tile::Wood) {//if the tile above them is wood. has to be updtated for player facing location
				player.timeCuttingDownTree++;
					if (player.timeCuttingDownTree >= 100) {//if they've been cutting down a tree for a while
						map.chopTree(map.Trees[{map.Tiles[{ tileAbovePlayer.x, tileAbovePlayer.y }]->parentOrigin.x, map.Tiles[{ tileAbovePlayer.x, tileAbovePlayer.y }]->parentOrigin.y}], &player);
						player.timeCuttingDownTree = 0;
					}
			}
			else {
				player.timeCuttingDownTree = 0;
			}

		}
	}
	player.move(velocity);

	gameWindow.clear(sf::Color::White);
	
	gameWindow.clear(sf::Color(23, 230, 54, 255));

	camera.setCenter(player.getPosition());
	
	//Camera is bounded so that if the player goes to the top left of the level, the camera stops following.
	//This will be implemented for all corners once we have an actual background
	if (camera.getCenter().x < width / 2)
		camera.setCenter(width / 2, camera.getCenter().y);
	if (camera.getCenter().y < height / 2)  
		camera.setCenter(camera.getCenter().x, height / 2);

	gameWindow.setView(camera);
	//Temp//
	//gameWindow.draw(bgSprite);
	gameWindow.draw(level);
	////////

	if (map.timeSinceLastRenderCheck == 0) {//update the player position. only happens once every 12 frames.
		map.playerPos = player.findIntegerPlayerPosition(player.getPosition());
		
	}

	map.renderMoreTiles(map.playerPos, map.timeSinceLastRenderCheck);
	map.timeSinceLastRenderCheck++;
	
	if (map.timeSinceLastRenderCheck > 12) {
		map.timeSinceLastRenderCheck = 0;
	}
	
	gameWindow.draw(map);	
	gameWindow.draw(player);
	
	
	

	gameWindow.display();

}
