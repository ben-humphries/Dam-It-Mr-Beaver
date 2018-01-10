#pragma once
using namespace std;
#include <iostream>
#include <SFML\Graphics.hpp>
//#include <SFML\Graphics.hpp>
class Tile : public sf::Drawable, public sf::Transformable
{
public:
	Tile(std::string dir);
	Tile(std::string dir, sf::IntRect rectangle);
	~Tile();
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};