#pragma once
#include "Tile.h"
class Tree {
public:
	Tree(int width, int height, int startx, int starty, std::vector<int> IstartCoordinate);
	sf::Vector2<int> size;
	std::vector<int> treeTiles;
	sf::Vector2<int> startCoordinate;
	~Tree();
	void cutDown();
	enum treeStates {
		Standing,
		Fallen,
		Sapling
	};
	treeStates treeState = Standing;
};
