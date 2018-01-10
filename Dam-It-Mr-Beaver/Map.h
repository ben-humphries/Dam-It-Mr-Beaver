#pragma once
#include "Tile.h"
const int mapHeight = 30;
const int mapWidth = 30; 
const int numberTileTypes = 5;
const float tileWidthHeight = 1;
class Map {	
public:

	Tile * Tile1 = new Tile("Tile1");
	Tile * Tile2 = new Tile("Tile2");
	Tile * Tile3 = new Tile("Tile3");
	Tile * Tile4 = new Tile("Tile4");
	Tile * Tile5 = new Tile("Tile5");

	std::vector <Tile *> tempTyles;
	std::map < std::tuple<float, float>, Tile *> Tyles;
	void initializeTiles();

};