#include "Map.h"
Map::Map() {
	initializeTiles();
}
Map::~Map() {

}
void Map::initializeTiles() {
	int x = 75;
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			int y = rand() % howmanytyletypesthismanytyletypes;
			sf::IntRect reect(x * y + (5 * (y + 1)), 0, x, x + 5);
			Tile * tempTyle = new Tile("res/TexturePack1.png", reect);
			Tyles[{i, j}] = tempTyle;
			Tyles[{i, j}]->sprite.setPosition(i* 75, j* 75);
		}
	}
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			target.draw(* Tyles.at({i, j}), states);
		}
	}
}