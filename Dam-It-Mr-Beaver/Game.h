#pragma once
#include "SFML/Graphics.hpp"

#include "Player.h"

class Game
{
public:

	static enum GameState {
		Uninitialized,
		Paused,
		Running,
		Exiting
	};

	static int Init();
	static void Start();
	static void Update();

	static GameState gameState;

	static sf::RenderWindow gameWindow;
	static sf::View camera;

	static clock_t t;

	static Player player;

};

