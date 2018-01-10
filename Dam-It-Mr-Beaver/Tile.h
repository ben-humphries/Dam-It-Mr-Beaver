#pragma once
using namespace std;
#include <iostream>
#include "SFML\Graphics.hpp"
class Tile {
public:
	Tile(std::string dir);
	~Tile();
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};