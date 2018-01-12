#pragma once
#include "Tile.h"

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();

	

	std::vector <Tile *> tempTyles;
	std::map < std::tuple<float, float>, Tile *> Tyles;
	std::map < std::tuple<float, float>, Tile *> flowerTyles;
	std::map < std::tuple<float, float>, bool> flowerCheck; //this is to know if there is a flower at a location. very inefficient, should be fixed.
	void initializeTiles();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};