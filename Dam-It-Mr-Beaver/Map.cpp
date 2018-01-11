#include "Map.h"
Map::Map() {
	initializeTiles();
}
Map::~Map() {

}
void Map::initializeTiles() {
	//sizeofpicture is me figuring out how big each tile is in the texture pack, will be better when we have photoshop
	int sizeofpicture = 32;
	int scale = 5;
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			int howfaracross = (rand() % howmanytyletypesthismanytyletypes);//gives a value between 0 and the number of tyle types
			int howfardown = 0;
			
			//if there are, say, 64 tiles, we need a way to get to a tile in the middle.
			//of a texture pack that's 8 by 8. if we get tile number 27, a tile in the 4th row,
			//we go tile 27 which is greater than 8, 19 is greater than 8, 11, 3. we know the tile is 3 from the right. we also know it's 3 down (first row is 0 down)
			//bam, we have the right tile. 
			while (howfaracross >= howmanyinrow) {
				howfaracross -= howmanyinrow;
				howfardown += 1;
			}
			sf::IntRect reect(howfaracross * sizeofpicture + (0 * (howfaracross + 1)), howfardown * sizeofpicture + (0*(howfardown + 1)), sizeofpicture, sizeofpicture + 5);
			Tile * tempTyle = new Tile("res/Working on grassssss.png", reect);
			tempTyle->sprite.setPosition(i* sizeofpicture*scale, j* sizeofpicture*scale);
			tempTyle->sprite.scale(scale, scale);
			Tyles[{i, j}] = tempTyle;
			
			//Tyles[{i, j}]->sprite.setPosition(i* sizeofpicture*scale, j* sizeofpicture*scale);
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