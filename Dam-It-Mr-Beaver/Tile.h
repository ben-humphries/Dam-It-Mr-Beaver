#pragma once
using namespace std;
#include <iostream>
#include <SFML\Graphics.hpp>
//#include <SFML\Graphics.hpp>

const int flowerTypeCount = 11;

const int heightofflower = 3;
const int widthofflower = 3;

static const int sizeofpicture = 16;
static const int scaleValue = 10;
class Tile : public sf::Drawable, public sf::Transformable
{
public:
	sf::Vector2<int> parentOrigin; //this stores the location of the parent tree/river/house
	Tile(std::string dir);
	Tile(std::string dir, sf::IntRect rectangle);
	Tile(int spriteIDi);
	~Tile();
	sf::Texture texture;
	sf::Sprite sprite;
	enum TyleType {
		Grass,
		Water,
		Wood,
		LeafyLeaf,
		Sapling,
		Brick
	};
	TyleType tyleType = Grass;
	bool shouldDraw = false;
	int spriteID;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void initiateFlowers();
	std::map<std::tuple <float, float>, int> flowerLocations;
};