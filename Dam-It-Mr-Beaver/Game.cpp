#include "Game.h"

sf::RenderWindow Game::gameWindow;
Game::GameState Game::gameState;

const int width = 800;
const int height = 600;

int Game::Init() {
	gameState = Uninitialized;

	gameWindow.create(sf::VideoMode(width, height), "Dam It Mr Beaver");
	
	gameState = Paused;

	return 0;
}

void Game::Start() {
	gameState = Running;

	while (gameState != Exiting) {
		Update();
	}
	
}

void Game::Update() {

	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			gameWindow.close();
			gameState = Exiting;
		}
	}

	gameWindow.clear();
	gameWindow.display();

}
