#pragma once
using namespace std;
#include <SFML\Graphics.hpp>
//#include <SFML\Graphics.hpp>
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