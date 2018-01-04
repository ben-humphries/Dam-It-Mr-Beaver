#include "Player.h"



Player::Player(std::string dir)
{
	if (!texture.loadFromFile(dir)) {
		printf("Could not load player texture");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}


Player::~Player()
{
}

//Overloads Transformable move() function to move our sprite as well.
//There may be a way to do this by calling the parent function before adding our own stuff,
//but move() is easy so I just rewrote it
void Player::move(float x, float y) {
	sf::Vector2f position = getPosition();
	setPosition(position.x + x, position.y + y);

	sprite.setPosition(position.x + x, position.y + y);
}

//Required overload of Drawable draw(), to draw our sprite when we call gameWindow.draw(player)
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
