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

void Player::move(float x, float y) {
	sf::Vector2f position = getPosition();
	setPosition(position.x + x, position.y + y);

	sprite.setPosition(position.x + x, position.y + y);
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
