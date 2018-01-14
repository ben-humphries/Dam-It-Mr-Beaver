#include "Map.h"
Map::Map() {
	initializeTiles();
}
Map::~Map() {

}
void Map::initializeTiles() {
	//sizeofpicture is me figuring out how big each tile is in the texture pack, will be better when we have photoshop
	

	for (float i = 0; i < mapHeight; i += 1) {
		for (float j = 0; j < mapWidth; j += 1) {
			
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
			tempTyle->sprite.setPosition(j* sizeofpicture * scaleValue, i* sizeofpicture * scaleValue);
			tempTyle->sprite.scale(scaleValue, scaleValue);
			tempTyle->initiateFlowers(); //set up the flowers of r that tile
			Tyles[{j, i}] = tempTyle;
			
			for (float k = i * sizeofpicture; k < i* sizeofpicture + sizeofpicture; k += heightofflower) { //iterate from the top to the bottom of the current tile (i is top)

				for (float l = j *sizeofpicture; l < j*sizeofpicture + sizeofpicture; l += widthofflower) {//go from left to right at that current lenght checking for flower 
					
					flowerCheck[{l, k}] = false;
					//cout << tempTyle->flowerLocations.at({ l, k }) << endl;
					if (tempTyle->flowerLocations.at({ l, k }) != -1) { //if there is a flower there
						//cout << "yee" << endl;
						sf::IntRect reect(tempTyle->flowerLocations.at({ l, k }) * widthofflower, 4 * sizeofpicture, widthofflower, heightofflower); //find the sprite location for that flower
						Tile * tempTyle2 = new Tile("res/grasstest2.png", reect); //and make a new tile for that flower
						tempTyle2->sprite.setPosition(l * scaleValue, k  * scaleValue);
						tempTyle2->sprite.scale(scaleValue , scaleValue);
						flowerTyles[{l, k}] = tempTyle2;        
						flowerCheck[{l, k}] = true;
					}
				}
			}
			
			
		}
	}

	River * river1 = new River(4, 4, 9, 9); //remember that coordinates start at 0, 0
	//this push_back system can probably be solved during initialization, i just don't know how. BEN HOW
	river1->riverTiles.push_back(0); river1->riverTiles.push_back(0); river1->riverTiles.push_back(0); river1->riverTiles.push_back(0);
	river1->riverTiles.push_back(1); river1->riverTiles.push_back(1); river1->riverTiles.push_back(1); river1->riverTiles.push_back(0); 
	river1->riverTiles.push_back(0); river1->riverTiles.push_back(0); river1->riverTiles.push_back(0); river1->riverTiles.push_back(0);
	river1->riverTiles.push_back(1); river1->riverTiles.push_back(1); river1->riverTiles.push_back(1); river1->riverTiles.push_back(1);
	setupRiver(river1);
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	for (float i = 0; i < mapHeight; i += tileWidthHeight) {
		for (float j = 0; j < mapWidth; j += tileWidthHeight) {
			target.draw(*Tyles.at({ j, i }), states);
			for (float k = i *sizeofpicture; k < i * sizeofpicture + sizeofpicture; k += heightofflower) {

				for (float l = j * sizeofpicture; l < j * sizeofpicture + sizeofpicture; l += widthofflower) {
					if (flowerCheck.at({ l, k })) {
						
						//target.draw(*flowerTyles.at({ l, k }), states); not going to draw flowers for now, too many to be good
					}
				}
			}
		}
	}
}
void Map::setupRiver(River * river) {
	int arraytracker = 0;
	for (int i = river->startCoordinate.y; i < river->startCoordinate.y + river->size.y; i += 1) { //because the map coordinates and river size are in the same 1 per 1 tile system, += 1
		//this one actual does have to do .y first, then .x to make the push_back system work nicely
		for (int j = river->startCoordinate.x; j < river->startCoordinate.x + river->size.x; j += 1) {
			
			if (river->riverTiles.at(arraytracker) != 0) {
				sf::IntRect reect(15 *sizeofpicture, 15 * sizeofpicture, sizeofpicture, sizeofpicture); 

				//sf::IntRect reect(0, 0, 0, 0);
				Tile * tempTyle = new Tile("res/grasstest2.png", reect);
				tempTyle->sprite.setPosition(i* sizeofpicture * scaleValue, j* sizeofpicture * scaleValue);
				tempTyle->sprite.scale(scaleValue, scaleValue);
				Tyles[{j, i}] = tempTyle; 
			}
			arraytracker++;
		}
		
	}
}