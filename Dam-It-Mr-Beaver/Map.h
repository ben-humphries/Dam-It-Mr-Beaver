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
	void initializeTiles();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};