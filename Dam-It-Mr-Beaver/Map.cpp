#include "Map.h"
Map::Map() {
	initializeTiles();
}
Map::~Map() {

}
void Map::initializeTiles() {
	//sizeofpicture is me figuring out how big each tile is in the texture pack, will be better when we have photoshop
	
	if (!tileTexture.loadFromFile("res/grasstest2.png")) {
		printf("Could not load tile spritesheet");
	}
	int x = 0;
	int y = 0;
	
	rect.height = sizeofpicture;
	rect.width = sizeofpicture;
	rect.left = 0;
	rect.top = 0;
	for (int i = 0; i < numberOfGrassTiles; i++) { //this sets up the 64 grass sprites we use to make the whole map. the tile class then refrences somewhere inside this vector of sprites

		sf::Sprite * tempTileSprite = new sf::Sprite;
		tempTileSprite->setTexture(tileTexture); //possibly can do this outside the for loop, unsure though

		tempTileSprite->setTextureRect(rect);
		tempTileSprite->scale(scaleValue, scaleValue);
		tileSprites.push_back(tempTileSprite);
		x++;
		if (x >= 16) {
			x = 0;
			y++;
			rect.top = y * sizeofpicture;
		}
		rect.left = x * sizeofpicture;
	}
	x = 0; 
	y = 0;
	for (int i = 0; i < numberOfRiverTiles; i++) {
		sf::Sprite * tempTileSprite = new sf::Sprite;
		tempTileSprite->setTexture(tileTexture); //possibly can do this outside the for loop, unsure though

		rect.left = (14 * sizeofpicture) + x * sizeofpicture;
		rect.top = (14 * sizeofpicture) + y * sizeofpicture;
		tempTileSprite->setTextureRect(rect);
		tempTileSprite->scale(scaleValue, scaleValue);
		tileSprites.push_back(tempTileSprite);
		x++;
		if (x >= 2) {
			x = 0;
			y++;
			rect.top = y * sizeofpicture;
		}

	}
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			int tileID = rand() % numberOfGrassTiles;//gives a value between 0 and the number of tile types
			Tile * tempTile = new Tile(tileID);

			Tiles[{i, j}] = tempTile;
		}
	}

	/* killing all of this, was old an innefecient. will delete when other thing twerks. 
	for (float i = 0; i < mapHeight; i += 1) {
		for (float j = 0; j < mapWidth; j += 1) {

			int tileID = (rand() % numberOfGrassTileTypes);//gives a value between 0 and the number of tile types

			int x = tileID;
			int y = 0;

			//if there are, say, 64 tiles, we need a way to get to a tile in the middle.
			//of a texture pack that's 8 by 8. if we get tile number 27, a tile in the 4th row,
			//we go tile 27 which is greater than 8, 19 is greater than 8, 11, 3. we know the tile is 3 from the right. we also know it's 3 down (first row is 0 down)
			//bam, we have the right tile. 
			while (x >= howmanyinrow) {
				x -= howmanyinrow;
				y += 1;
			}

			sf::IntRect reect(x * sizeofpicture, y * sizeofpicture, sizeofpicture, sizeofpicture);
			
			Tile * tempTile = new Tile("res/grasstest2.png", reect);
			tempTile->sprite.setPosition(j* sizeofpicture * scaleValue, i* sizeofpicture * scaleValue);
			tempTile->sprite.scale(scaleValue, scaleValue);
			//tempTile->initiateFlowers(); //set up the flowers of r that tile. commented out to reduce lag?
			Tiles[{j, i}] = tempTile;
			/*
				for (float k = i * sizeofpicture; k < i* sizeofpicture + sizeofpicture; k += heightofflower) { //iterate from the top to the bottom of the current tile (i is top)

					for (float l = j *sizeofpicture; l < j*sizeofpicture + sizeofpicture; l += widthofflower) {//go from left to right at that current lenght checking for flower 

						flowerCheck[{l, k}] = false;
						//cout << tempTile->flowerLocations.at({ l, k }) << endl;
						if (tempTile->flowerLocations.at({ l, k }) != -1) { //if there is a flower there
							//cout << "yee" << endl;
							sf::IntRect reect(tempTile->flowerLocations.at({ l, k }) * widthofflower, 4 * sizeofpicture, widthofflower, heightofflower); //find the sprite location for that flower
							Tile * tempTile2 = new Tile("res/grasstest2.png", reect); //and make a new tile for that flower
							tempTile2->sprite.setPosition(l * scaleValue, k  * scaleValue);
							tempTile2->sprite.scale(scaleValue, scaleValue);
							flowerTiles[{l, k}] = tempTile2;
							flowerCheck[{l, k}] = true;
						}
					}
				
			}
			
		}
		
	}
	*/
	River * river1 = new River(8, 8, 9, 9,
	{ 1, 1, 1, 1, 1, 1, 1, 1,
	  0, 0, 0, 0, 0, 0, 1, 1, 
      1, 1, 1, 1, 1, 0, 1, 1,
	  1, 0, 0, 0, 0, 0, 1, 1,
	  1, 0, 1, 1, 1, 0, 1, 1,
	  1, 0, 1, 1, 1, 0, 1, 1,
	  1, 0, 0, 0, 0, 0, 1, 1,
	  1, 1, 1, 1, 1, 1, 1, 1}); //remember that coordinates start at 0, 0
	  setupRiver(river1); 

}  


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	sf::Vector2<int> start;
	sf::Vector2<int> end;

	for (float i = 0; i < mapHeight; i += 1) {
		for (float j = 0; j < mapWidth; j += 1) {
			if (Tiles.at({ j, i })->shouldDraw) {
				tileSprites.at(Tiles.at({ j, i })->spriteID)->setPosition(j * sizeofpicture * scaleValue, i*  sizeofpicture * scaleValue);
				target.draw(* tileSprites.at(Tiles.at({ j, i })->spriteID), states);
			}
			}
		}
	}
void Map::whatTilesToDraw(sf::Vector2<int> playerPos) {
	
	for (float i = 0; i < mapHeight; i += 1) {
		for (float j = 0; j < mapWidth; j += 1) {
			Tiles.at({ j, i })->shouldDraw = false;
			if (abs(playerPos.x - j) < 8 && abs(playerPos.y - i) < 7) { //change to 6 and 4 to test
				Tiles.at({ j, i })->shouldDraw = true;
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
				int tileID = rand() % numberOfRiverTiles + numberOfGrassTiles; //gives a number between 64 and 67, where the thing is in the sprites array
				Tile * tempTile = new Tile(tileID);
				Tiles[{j, i}] = tempTile; 
			}
			arraytracker++;
		}
		
	}
}