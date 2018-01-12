#include "Map.h"
Map::Map() {
	initializeTiles();
}
Map::~Map() {

}
void Map::initializeTiles() {
	//sizeofpicture is me figuring out how big each tile is in the texture pack, will be better when we have photoshop
	

	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			
			int tyleID = (rand() % numberOfGrassTyleTypes);//gives a value between 0 and the number of tyle types
			int howfaracross = tyleID;
			int howfardown = 0;
			
			//if there are, say, 64 tiles, we need a way to get to a tile in the middle.
			//of a texture pack that's 8 by 8. if we get tile number 27, a tile in the 4th row,
			//we go tile 27 which is greater than 8, 19 is greater than 8, 11, 3. we know the tile is 3 from the right. we also know it's 3 down (first row is 0 down)
			//bam, we have the right tile. 
			while (howfaracross >= howmanyinrow) {
				howfaracross -= howmanyinrow;
				howfardown += 1;
			}
			sf::IntRect reect(howfaracross * sizeofpicture, howfardown * sizeofpicture, sizeofpicture, sizeofpicture);
			Tile * tempTyle = new Tile("res/grasstest2.png", reect);
			tempTyle->sprite.setPosition(j* sizeofpicture*scaleValue, i* sizeofpicture*scaleValue);
			tempTyle->sprite.scale(scaleValue, scaleValue);
			tempTyle->initiateFlowers(); //set up the flowers of r that tile
			Tyles[{j, i}] = tempTyle;
			
			for (float k = i * sizeofpicture; k < i + sizeofpicture; k += heightofflower) { //iterate from the top to the bottom of the current tile (i is top)

				for (float l = j *sizeofpicture; l < j + sizeofpicture; l += widthofflower) {//go from left to right at that current lenght checking for flower 
					cout << l << " " << k << endl;
					if (tempTyle->flowerLocations.at({ l, k }) != -1) { //if there is a flower there
						sf::IntRect reect(tempTyle->flowerLocations.at({ l, k }) * widthofflower, 4 * sizeofpicture, widthofflower, heightofflower); //find the sprite location for that flower
						Tile * tempTyle2 = new Tile("res/grasstest2.png", reect); //and make a new tile for that flower
						tempTyle2->sprite.setPosition(l * widthofflower * scaleValue, k * widthofflower * scaleValue);
						tempTyle2->scale(scaleValue, scaleValue);
						flowerTyles[{l, k}] = tempTyle2;
					}
				}
			}
			cout << "done with that" << j << i << endl;
			
			
		}
	}
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	cout << "here1" << endl;
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			target.draw(* Tyles.at({j, i}), states);
			for (float k = i; k < i + sizeofpicture; k += heightofflower) {

				for (float l = j; l < j + sizeofpicture; l += widthofflower) {
					target.draw(*flowerTyles.at({ l, k }), states);
				}
			}
		}
	}
	cout << "here2" << endl;
}