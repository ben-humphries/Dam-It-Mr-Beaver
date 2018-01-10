#pragma once
#include "Tile.h"
const int mapHeight = 30;
const int mapWidth = 30; 
const int howmanytyletypesthismanytyletypes = 5;
const float tileWidthHeight = 1;
class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();

	

	std::vector <Tile *> tempTyles;
	std::map < std::tuple<float, float>, Tile *> Tyles;
	void initializeTiles();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};