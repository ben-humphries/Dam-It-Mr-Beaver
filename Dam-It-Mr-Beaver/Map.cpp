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
	for (int i = 0; i < numberOfTreeTiles; i++) { //setup tree sprites
		sf::Sprite * tempTileSprite = new sf::Sprite;
		tempTileSprite->setTexture(tileTexture);
		rect.left = (12 * sizeofpicture) + x * sizeofpicture;
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
	x = 0;
	y = 0;
	for (int i = 0; i < numberOfRiverTiles; i++) { //setup river sprites
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
		for (int j = 0; j < mapHeight; j++) { //do the initial tile render. out of date but will use for now.
			tileRendered[{i, j}] = true;
			int tileID = rand() % numberOfGrassTiles;//gives a value between 0 and the number of tile types
			Tile * tempTile = new Tile(tileID);

			Tiles[{i, j}] = tempTile;
		}
	}

	River * river1 = new River(8, 8, 9, 9,
	{ 1, 1, 1, 1, 1, 1, 1, 1,
	  0, 0, 0, 0, 0, 0, 1, 1,
	  1, 1, 1, 1, 1, 0, 1, 1,
	  1, 0, 0, 0, 0, 0, 1, 1,
	  1, 0, 1, 1, 1, 0, 1, 1,
	  1, 0, 1, 1, 1, 0, 1, 1,
	  1, 0, 0, 0, 0, 0, 1, 1,
	  1, 1, 1, 1, 1, 1, 1, 1 }); //remember that coordinates start at 0, 0
	setupRiver(river1);
	Tree * tree1 = new Tree(3, 3, 1, 1, { //position is for top left of the thing, not bot right
		0, 2, 0,
		2, 2, 2,
		0, 1, 0
	});
	setupTree(tree1);	
}  


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	for (float i = playerPos.y - 9; i < playerPos.y + 9; i += 1) {
		for (float j = playerPos.x - 10; j < playerPos.x + 10; j += 1) {
			if (i >= 0 && j >= 0) {
				
				tileSprites.at(Tiles.at({ j, i })->spriteID)->setPosition(j * sizeofpicture * scaleValue, i*  sizeofpicture * scaleValue);

				target.draw(*tileSprites.at(Tiles.at({ j, i })->spriteID), states);
				

			}
		}
	}
}
void Map::whatTilesToDraw(sf::Vector2<int> playerPos) {
	
	for (float i = 0; i < mapHeight; i += 1) {
		for (float j = 0; j < mapWidth; j += 1) {
			Tiles.at({ j, i })->shouldDraw = false;
			if (abs(playerPos.x - j) < 10 && abs(playerPos.y - i) < 8.5) {
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
				int tileID = rand() % numberOfRiverTiles + numberOfGrassTiles + numberOfTreeTiles; //gives a number between 64 and 67, where the thing is in the sprites array
				Tiles[{j, i}]->spriteID = tileID;
			}
			arraytracker++;
		}
		
	}
}
void Map::setupTree(Tree * tree) { 
int arraytracker = 0;
int tileID = 0;
	for (int i = tree->startCoordinate.y; i < tree->startCoordinate.y + tree->size.y; i += 1) { //because the map coordinates and river size are in the same 1 per 1 tile system, += 1
		//this one actual does have to do .y first, then .x to make the push_back system work nicely
		for (int j = tree->startCoordinate.x; j < tree->startCoordinate.x + tree->size.x; j += 1) {
			switch (tree->treeTiles.at(arraytracker)) {
			case 0:
				//cout << Tiles[{j, i}]->spriteID << endl;
				break; //just don't change it, stay greeeeeen

			case 1:
				tileID = rand() % 2 + numberOfGrassTiles; //gives a number between 64 and 65, where the wood sprites are in the sprites array
				
				Tiles[{j, i}]->spriteID = tileID;
				//cout << Tiles[{j, i}]->spriteID << endl;
				break;
			case 2:
				tileID = rand() % 2 + numberOfGrassTiles + 2; //gives a number between 66 and 67, where the leaf sprites are in the sprites array
				Tiles[{j, i}]->spriteID = tileID;
				//cout << Tiles[{j, i}]->spriteID << endl;
				break;
			default :
				cout << "added some new wood tiles, didya dummy" << endl;
				break;
			}
			arraytracker++;
		}		
	}
}
void Map::renderMoreTiles(sf::Vector2<int> playerPos) { //basically every 15 frames this function renders the tiles in a 30x30 box around the player
	/*for (int i = playerPos.x - 15; i < playerPos.x + 15; i++) {
		for (int j = playerPos.y - 15; j < playerPos.y + 15; j++) {
			int tileID = rand() % numberOfGrassTiles;
			Tile * tempTile = new Tile(tileID);
			Tiles[{i, j}] = tempTile;
		}
	}
	*/
	int widthOfRenderBox = 32;
	int tileID = 0;
	for (int i = 0; i < 2; i++) { //we run this whole thing twice so the rendered layer is two thick
		widthOfRenderBox -= 2;
		int startx = playerPos.x - widthOfRenderBox / 2;
		int starty = playerPos.y - widthOfRenderBox / 2;
		
		for (int i = startx; i < startx + widthOfRenderBox; i++) { // go across the 30 by 30 box (left to right), render the top edges
			if (i >= 0) {

				tileID = rand() % numberOfGrassTiles;
				Tile * tempTile = new Tile(tileID);
				Tiles[{i, starty}] = tempTile; //this will overwrite rivers, trees. NEEDS FIX AHAHAGAHAHAHAh
				tileID = rand() % numberOfGrassTiles;
				Tile * tempTile2 = new Tile(tileID);
				Tiles[{i, starty + widthOfRenderBox}] = tempTile2;
			}
		}
		for (int i = starty; i < starty + widthOfRenderBox + 1; i++) {//go down the edges, do the edges. moved by 1 bc for some reason the bottom right corner wouldn't render and it crashed LOL
			if (i >= 0) {
				tileID = rand() % numberOfGrassTiles;
				Tile * tempTile = new Tile(tileID);
				Tiles[{startx, i}] = tempTile;
				tileID = rand() % numberOfGrassTiles;
				Tile * tempTile2 = new Tile(tileID);
				Tiles[{startx + widthOfRenderBox, i}] = tempTile2;
				if (startx + 30 == 30 && i == 0) {
					cout << "did it" << endl;
				}
			}
		}
	}
	
}
void Map::renderMoreTilesBig(sf::Vector2<int> playerPos) {
	for (float i = playerPos.y - 250; i < playerPos.y + 250; i += 1) {
		for (float j = playerPos.x - 250; j < playerPos.x + 250; j += 1) {
			if (i >= 0 && j >= 0) {
				//if (abs(playerPos.x - j) > 10 && abs(playerPos.y - i) > 8.5) {//if it's outside the FOV
					Tiles[{j, i}] = NULL; //set to null so when the draw function calls it the game no break
				//}
			}
		}
	}
	for (int i = playerPos.x - 10; i < playerPos.x + 10; i++) {
		for (int j = playerPos.y - 9; j < playerPos.y + 9; j++) { //do the initial tile render. out of date but will use for now.
			if (i >= 0 && j >= 0) {
				int tileID = rand() % numberOfGrassTiles;//gives a value between 0 and the number of tile types
				Tile * tempTile = new Tile(tileID);

				Tiles[{i, j}] = tempTile;
			}
		}
	}
}