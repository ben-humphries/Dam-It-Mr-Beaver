#pragma once
using namespace std;
#include <iostream>
#include <SFML\Graphics.hpp>
//#include <SFML\Graphics.hpp>
const int flowerTypeCount = 11;
const int mapHeight = 30;
const int mapWidth = 30;
const int numberOfGrassTyleTypes = 64;
const int numberOfFlowerTyleTypes = 0;
const float tileWidthHeight = 1;
const int howmanyinrow = 16;
const int sizeofpicture = 16;
const int heightofflower = 3;
const int widthofflower = 3;
const int scaleValue = 10; 
class Tile : public sf::Drawable, public sf::Transformable
{
public:
	Tile(std::string dir);
	Tile(std::string dir, sf::IntRect rectangle);
	~Tile();
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void initiateFlowers();
	std::map<std::tuple <float, float>, int> flowerLocations;
};