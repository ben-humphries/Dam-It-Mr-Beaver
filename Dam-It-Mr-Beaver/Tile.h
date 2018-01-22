#pragma once
using namespace std;
#include <iostream>
#include <SFML\Graphics.hpp>
//#include <SFML\Graphics.hpp>

const int flowerTypeCount = 11;
const int mapHeight = 30;
const int mapWidth = 30;
const int numberOfGrassTileTypes = 64;
const int numberOfFlowerTileTypes = 0;
const float tileWidthHeight = 1;
const int howmanyinrow = 16;
const int heightofflower = 3;
const int widthofflower = 3;
class Tile : public sf::Drawable, public sf::Transformable
{
public:

	static const int sizeofpicture = 16;
	static const int scaleValue = 10;
	Tile(std::string dir);
	Tile(std::string dir, sf::IntRect rectangle);
	~Tile();
	sf::Texture texture;
	sf::Sprite sprite;
	enum TyleType {
		Grass,
		Water,
		Wood,
		Brick
	};
	TyleType tyleType = Grass;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void initiateFlowers();
	std::map<std::tuple <float, float>, int> flowerLocations;
};