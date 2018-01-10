#include "Map.h"
Map::Map() {
	initializeTiles();
}
void Map::initializeTiles() {
	/*
	tempTyles.clear();
	tempTyles.push_back(Tile1);
	tempTyles.push_back(Tile2);
	tempTyles.push_back(Tile3);
	tempTyles.push_back(Tile4);
	tempTyles.push_back(Tile5);
	*/
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			sf::IntRect reect(0, 30 * (rand() % 5), 30, 30);
			Tile * tempTyle = new Tile("res/TexturePack1.png", reect);
			Tyles[{i, j}] = tempTyle;
			Tyles[{i, j}]->sprite.setPosition(i, j);
		}
	}
}