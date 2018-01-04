#include "Game.h"

Game::GameState Game::gameState;

sf::RenderWindow Game::gameWindow;
sf::View Game::camera;

const int width = 800;
const int height = 600;

clock_t Game::t;

Player Game::player("res/player.png");

//Temp//

sf::Texture bgTexture;
sf::Sprite bgSprite;

////////

int Game::Init() {
	gameState = Uninitialized;

	gameWindow.create(sf::VideoMode(width, height), "Dam It Mr Beaver");
	camera.setSize(width, height);
	camera.setCenter(width / 2, height / 2);
	
	gameState = Paused;

	//Temp//

	bgTexture.loadFromFile("res/background.png");
	bgSprite.setTexture(bgTexture);

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
	float speed = 500.0f;

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
	
	//Temp//
	gameWindow.draw(bgSprite);
	////////

	gameWindow.draw(player);
	camera.setCenter(player.getPosition());

	//Camera is bounded so that if the player goes to the top left of the level, the camera stops following.
	//This will be implemented for all corners once we have an actual background
	if (camera.getCenter().x < width / 2)
		camera.setCenter(width / 2, camera.getCenter().y);
	if (camera.getCenter().y < height / 2)
		camera.setCenter(camera.getCenter().x, height / 2);

	gameWindow.setView(camera);
	gameWindow.display();

}
