#pragma once
#include "River.h"
#include "Tree.h"
const int mapHeight = 30;
const int mapWidth = 30;
const int numberOfGrassTiles = 64;
const int numberOfTreeTiles = 4;
const int numberOfRiverTiles = 4;
const int numberOfFlowerTileTypes = 0;
const int howmanyinrow = 16;
static const int sizeofpicture = 16;

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();
	sf::Vector2<int> playerPos;
	sf::IntRect rect;
	sf::Texture tileTexture;
	float timeSinceLastRenderCheck = 0; //this tracks how long it's been since we've checked to render more tiles. infinitiiiiiiiiiiiiiiiiiiiii
	float timeSinceLastBigRenderCheck = 500; //this tracks how long it's been since we've made a huge block of tiles to null.
	std::vector <Tile *> tempTiles;
	std::vector <sf::Sprite *> tileSprites;
	std::map < std::tuple<int, int>, Tile *> Tiles;
	std::map < std::tuple<int, int>, Tree *> Trees;
	std::map < std::tuple<int, int>, River *> Rivers;
	std::vector <std::tuple<int, sf::Vector2<int>>> importantTiles; //stores the origins for the trees and rivers so they aren't drawn over
	std::map < std::tuple<float, float>, Tile *> flowerTiles;
	void initializeTiles();
	void renderMoreTiles(sf::Vector2<int> playerPos);
	void renderMoreTilesBig(sf::Vector2<int> playerPos);
	void renderRiver(River * river);
	void renderTree(Tree * tree);
	void setupRiver(River * river);
	void setupTree(Tree * tree); //as you can see, the tree and river setups are very similar. they could be merged into one master function, but that would require a lot of in function comparisons as the tiles grew in complexity. i think they should be seperate for now
	void chopTree(Tree * tree);
	void whatTilesToDraw(sf::Vector2<int> playerPos);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};