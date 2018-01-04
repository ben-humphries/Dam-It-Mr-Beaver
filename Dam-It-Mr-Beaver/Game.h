#pragma once
#include "SFML/Graphics.hpp"

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


};

