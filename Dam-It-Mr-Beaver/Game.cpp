#include "Game.h"

sf::RenderWindow Game::gameWindow;
Game::GameState Game::gameState;

const int width = 800;
const int height = 600;

clock_t Game::t;

Player Game::player("res/player.png");


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
	float speed = 100.0f;

	//Player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		player.move(0.0f, -speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		player.move(-speed * dt, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		player.move(0.0f, speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		player.move(speed * dt, 0.0f);
	}

	gameWindow.clear(sf::Color::White);

	gameWindow.draw(player);

	gameWindow.display();

}
