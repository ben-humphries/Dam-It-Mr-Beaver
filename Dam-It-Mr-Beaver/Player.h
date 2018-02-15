#include <SFML\Graphics.hpp>
#include "Inventory.h"
#include "Tile.h"
class Player : public sf::Drawable, public sf::Transformable
{
public:
	bool isCuttingDownTree = false; 
	int timeCuttingDownTree = 0; 
	Player(std::string dir);
	Inventory * inventory = new Inventory(); 
	~Player();

	sf::Texture texture;
	sf::Sprite sprite;

	virtual void move(sf::Vector2f velocity);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::Vector2<int> findIntegerPlayerPosition(sf::Vector2<float> position);
};

