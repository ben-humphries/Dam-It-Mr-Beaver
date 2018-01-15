#include "River.h"
River::River(int width, int height, int startx, int starty, std::vector<int> IstartCoordinate) {
	size.x = width;
	size.y = height;
	startCoordinate.x = startx;
	startCoordinate.y = starty;
	riverTiles = IstartCoordinate;
}