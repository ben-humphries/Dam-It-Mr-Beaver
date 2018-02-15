#pragma once
using namespace std;
#include <SFML\Graphics.hpp>
static int numberItemTypes = 4;

class Inventory {
public:
	enum ItemTypes {
		Grass,
		Wood,
		Flower,
		Brick
	};
	std::map<ItemTypes, int> items; //the vector stores quantity an
	
};