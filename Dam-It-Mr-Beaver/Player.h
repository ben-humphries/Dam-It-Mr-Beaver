#include <SFML\Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player(std::string dir);
	~Player();

	sf::Texture texture;
	sf::Sprite sprite;

	virtual void move(float x, float y);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

