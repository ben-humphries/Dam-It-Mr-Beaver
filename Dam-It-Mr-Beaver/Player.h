#include <SFML\Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player(std::string dir);
	~Player();

	sf::Texture texture;
	sf::Sprite sprite;

	virtual void move(sf::Vector2f velocity);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

