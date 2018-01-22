#pragma once
#include "River.h"
class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();
	
	

	std::vector <Tile *> tempTiles;
	std::map < std::tuple<float, float>, Tile *> Tiles;
	std::map < std::tuple<float, float>, Tile *> flowerTiles;
	std::map < std::tuple<float, float>, bool> flowerCheck; //this is to know if there is a flower at a location. very inefficient, should be fixed.
	void initializeTiles();
	void setupRiver(River * river);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};