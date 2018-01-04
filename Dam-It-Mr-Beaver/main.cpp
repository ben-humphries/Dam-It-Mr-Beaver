#include "Game.h"

int main()
{
	if (Game::Init() == 0) {
		Game::Start();
	}

	return 0;
}