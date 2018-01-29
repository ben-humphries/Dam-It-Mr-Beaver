#include "Tree.h"
Tree::Tree(int width, int height, int startx, int starty, std::vector<int> IstartCoordinate) {
	size.x = width;
	size.y = height;
	startCoordinate.x = startx;
	startCoordinate.y = starty;
	treeTiles = IstartCoordinate;
}