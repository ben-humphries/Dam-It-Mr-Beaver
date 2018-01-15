#pragma once
#include "Tile.h"
class River {
public:
	River(int width, int height, int startx, int starty, std::vector<int> IstartCoordinate);
	sf::Vector2<int> size;
	std::vector<int> riverTiles;
	sf::Vector2<int> startCoordinate;

};