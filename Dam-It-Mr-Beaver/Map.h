#pragma once
#include "River.h"

const int mapHeight = 30;
const int mapWidth = 30;
const int numberOfGrassTiles = 64;
const int numberOfRiverTiles = 4;
const int numberOfFlowerTileTypes = 0;
const int howmanyinrow = 16;
static const int sizeofpicture = 16;

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();
	
	sf::IntRect rect;
	sf::Texture tileTexture;
	float timeSinceLastDrawCheck = 500; //this calculates how long it's been since the last tile location analysis. I think i'll do it once every 5 frames.
	std::vector <Tile *> tempTiles;
	//std::vector <Tile *> Tiles;
	std::vector <sf::Sprite *> tileSprites;
	std::map < std::tuple<int, int>, Tile *> Tiles;
	std::map < std::tuple<float, float>, Tile *> flowerTiles;
	std::map < std::tuple<float, float>, bool> flowerCheck; //this is to know if there is a flower at a location. very inefficient, should be fixed.
	void initializeTiles();
	void setupRiver(River * river);
	void whatTilesToDraw(sf::Vector2<int> playerPos);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};