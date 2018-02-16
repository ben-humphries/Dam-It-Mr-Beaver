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
	
	sf::Sprite * tempTileSprite = new sf::Sprite;
	tempTileSprite->setTexture(tileTexture); 
	rect.left = 192;
	rect.top = 224;
	rect.height = 4;
	rect.width = 4; 
	tempTileSprite->setTextureRect(rect);
	tempTileSprite->scale(scaleValue, scaleValue);
	//above stuff was allll setting up the sprites



	//inventorySprites.at(Inventory::Wood) = { 0 , tempTileSprite }; //sets up the wood sprite
	
	//this next river is main river
	River * river1 = new River(25, 20, 5, 5, {

	});

	for (int i = 0; i < river1->size.x * river1->size.y; i++) {
		river1->riverTiles.push_back(1);
	}
	setupRiver(river1);

	Tree * tree1 = new Tree(3, 4, 1, 1, { //position is for top left of the thing, not bot right
		0, 2, 0,
		2, 2, 2,
		0, 1, 0,
		0, 1, 0
	});
	setupTree(tree1);
	Tree * tree2 = new Tree(3, 4, 27, 1, { //position is for top left of the thing, not bot right
		0, 2, 0,
		2, 2, 2,
		0, 1, 0,
		0, 1, 0
	});
	   setupTree(tree2);

	for (int i = 0; i < mapWidth; i++) { //set up the initial map
		for (int j = 0; j < mapHeight; j++) { //do the initial tile render. out of date but will use for now.
			
			int tileID = rand() % numberOfGrassTiles;//gives a value between 0 and the number of tile types
			Tile * tempTile = new Tile(tileID);
			Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ i, j }, tempTile));
			
		}
	}
	
}  


void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	

	for (float i = playerPos.y - 9; i < playerPos.y + 9; i += 1) {
		for (float j = playerPos.x - 9; j < playerPos.x + 9; j += 1) {
			if (i >= 0 && j >= 0) {
				//cout << j << " " << i << endl;
				
				tileSprites.at(Tiles.at({ j, i })->spriteID)->setPosition(j * sizeofpicture * scaleValue, i*  sizeofpicture * scaleValue);
				
				target.draw(*tileSprites.at(Tiles.at({ j, i })->spriteID), states);
				

			}
		}
	}

	
	/*
	if (std::get<0>(inventorySprites.at(Inventory::Wood)) > 0) {
		std::get<1>(inventorySprites.at(Inventory::Wood))->setPosition(10, 10);
		target.draw(*std::get<1>(inventorySprites.at(Inventory::Wood)));
	}
	*/
}

void Map::setupRiver(River * river) { //called when we're initally setting up the river
	int arraytracker = 0;
	for (int i = river->startCoordinate.y; i < river->startCoordinate.y + river->size.y; i += 1) { //because the map coordinates and river size are in the same 1 per 1 tile system, += 1
																								   //this one actual does have to do .y first, then .x to make the push_back system work nicely
		for (int j = river->startCoordinate.x; j < river->startCoordinate.x + river->size.x; j += 1) {
			Tile * tempTile = new Tile(0);
			tempTile->parentOrigin = river->startCoordinate;
			if (river->riverTiles.at(arraytracker) != 0) {
				int tileID = rand() % numberOfRiverTiles + numberOfGrassTiles + numberOfTreeTiles; //gives a number between 64 and 67, where the thing is in the sprites array
				tempTile->spriteID = tileID;	
				Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ j, i }, tempTile));
				river->sprites[{j, i }] = tileID; 

			}
			
			arraytracker++;
		}

	}
	Rivers[{ river->startCoordinate.x, river->startCoordinate.y }] = river;
	importantTiles.push_back({ 0, {river->startCoordinate.x, river->startCoordinate.y} });
	
	//renderRiver(river);
}
void Map::setupTree(Tree * tree) { 
	int arraytracker = 0;
	int tileID = 0;
	for (int i = tree->startCoordinate.y; i < tree->startCoordinate.y + tree->size.y; i += 1) { //because the map coordinates and river size are in the same 1 per 1 tile system, += 1
																								//this one actual does have to do .y first, then .x to make the push_back system work nicely
		for (int j = tree->startCoordinate.x; j < tree->startCoordinate.x + tree->size.x; j += 1) {
			Tile * tempTile = new Tile(0);
			tempTile->parentOrigin = tree->startCoordinate;
			
			switch (tree->treeTiles.at(arraytracker)) {
			case 0:
				break; //just don't change it, stay greeeeeen yyyyyyyyyyyyyeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
			case 1:
				tree->woodSize++;
				tileID = rand() % 2 + numberOfGrassTiles; //gives a number between 64 and 65, where the wood sprites are in the sprites array
				tempTile->spriteID = tileID;
				tree->sprites[{j, i}] = tileID;
				
				Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ j, i }, tempTile));
				Tiles[{j, i}]->tyleType = Tile::Wood;
				break;
			case 2:
				tileID = rand() % 2 + numberOfGrassTiles + 2; //gives a number between 66 and 67, where the leaf sprites are in the sprites array
				tempTile->spriteID = tileID;
				tree->sprites[{j, i}] = tileID;
				Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ j, i }, tempTile));
				break;
			default:
				cout << "added some new wood tiles, didya dummy" << endl;
				break;
			}
			arraytracker++;
		}
	}
	Trees[{ tree->startCoordinate.x, tree->startCoordinate.y }] = tree;
	importantTiles.push_back({ 1,{ tree->startCoordinate.x, tree->startCoordinate.y } });
	//renderTree(tree);
}
void Map::chopTree(Tree * tree, Player * player) {
	//player->inventory->items[Inventory::Wood] += tree->woodSize;
	//mapInventory = player->inventory; // i think this isn't necessary because of how i'm storing the sprites. will delete if so.
	//std::get<0>(inventorySprites.at(Inventory::Wood))+= tree->woodSize;
	int arrayCounter = 0;
	int tileID = 0;                                                                                                                                                                                                                                   
	for (int i = tree->startCoordinate.x; i < tree->startCoordinate.x + tree->size.x; i += 1) { //because the map coordinates and river size are in the same 1 per 1 tile system, += 1
		
		for (int j = tree->startCoordinate.y; j < tree->startCoordinate.y + tree->size.y; j += 1) {
			if (tree->sprites[{i, j}] >= numberOfGrassTiles) { // if it's not a grass tile 
				tileID = rand() % numberOfGrassTiles;
				Tiles[{i, j}]->spriteID = tileID;
				tree->sprites[{i, j}] = tileID;
		}
			tree->treeTiles.at(arrayCounter) = 0; //goes through and makes all the tree tiles grass. we need to do this too, the thing above is just for sprites
			arrayCounter++;
		}
	}
	int size = tree->treeTiles.size();
	int loc = size - ceil((float)tree->size.x / 2);
	tree->treeTiles.at(loc) = 1; //sets specifically the origin to 1 so it can be a sapling. 
	float tempXSize = tree->size.x; //ask ben bout this one
	tempXSize /= 2;
	tempXSize = floor(tempXSize); 
	tileID = rand() % numberOfWoodTiles + numberOfGrassTiles;
	tree->sprites[{ tree->startCoordinate.x + tempXSize, tree->startCoordinate.y + tree->size.y - 1 }] = tileID;
	Tiles[{tree->startCoordinate.x + tempXSize, tree->startCoordinate.y + tree->size.y - 1 }]->spriteID = tileID;
	Tiles[{ tree->startCoordinate.x + tempXSize, tree->startCoordinate.y + tree->size.y - 1 }]->tyleType = Tile::Sapling;
	tree->treeState = Tree::Sapling; //yeah it's messy. whateveeaiern qoienr qf fff . i think we need to keep track of both the treestate and the tyletype in enums tho, otherwise is confuse
	
}


void Map::renderMoreTiles(sf::Vector2<int> playerPos, int time) { //as time proceeds it slowly renders a 30 by 30 box around the dood. spread out to avoid spikes of low performance
	int widthOfRenderBox = 24;

	int localTime = time - widthOfRenderBox / 2;
	//time starts at 0 then goes up to 12. so it'll start at -12 and go to 0. 

	int startx = playerPos.x;
	int starty = playerPos.y;

	int tileID = rand() % numberOfGrassTiles;
	Tile * tempTile1 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ playerPos.x + localTime, starty - widthOfRenderBox / 2 }, tempTile1)); //do upper left

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile2 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ playerPos.x - localTime, starty - widthOfRenderBox / 2 }, tempTile2)); //do upper right

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile3 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ playerPos.x + localTime, starty + widthOfRenderBox / 2 }, tempTile3)); //do lower left


	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile4 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ playerPos.x - localTime, starty + widthOfRenderBox / 2 }, tempTile4)); //do lower right  

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile5 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ startx - widthOfRenderBox / 2, playerPos.y + localTime }, tempTile5)); //do upper left (redundent for first one

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile6 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ startx - widthOfRenderBox / 2, playerPos.y - localTime }, tempTile6)); //do lower left (reduntant for first one)

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile7 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ startx + widthOfRenderBox / 2, playerPos.y + localTime }, tempTile7)); //do lower right (redundant for first)

	tileID = rand() % numberOfGrassTiles;
	Tile * tempTile8 = new Tile(tileID);
	Tiles.insert(std::map<std::tuple<int, int>, Tile *>::value_type({ startx + widthOfRenderBox / 2, playerPos.y - localTime }, tempTile8)); //do upper left right (reduntant ofr first)

}