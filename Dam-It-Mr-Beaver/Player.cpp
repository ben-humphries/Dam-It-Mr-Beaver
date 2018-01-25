#include "Player.h"



Player::Player(std::string dir)
{
	if (!texture.loadFromFile(dir)) {
		printf("Could not load player texture");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(2.0f, 2.0f);
}


Player::~Player()
{
}

//Overloads Transformable move() function to move our sprite as well.
//There may be a way to do this by calling the parent function before adding our own stuff,
//but move() is easy so I just rewrote it
void Player::move(sf::Vector2f velocity) {
	
	Transformable::move(velocity);

	sprite.setPosition(getPosition());
}

//Required overload of Drawable draw(), to draw our sprite when we call gameWindow.draw(player)


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);

}
 

sf::Vector2<int> Player::findIntegerPlayerPosition(sf::Vector2<float> position) {
	sf::Vector2<int> playerCenterPos;
	sf::Vector2<int> tempPos;
	tempPos.x = position.x / (scaleValue * sizeofpicture);
	tempPos.y = position.y / (scaleValue * sizeofpicture);
	if (tempPos.x - floor(tempPos.x) < .5) { //if tempPos.x would round down
		tempPos.x = floor(tempPos.x);
	}
	else {
		tempPos.x = ceil(tempPos.x);
	}
	if (tempPos.y - floor(tempPos.y) < .5) { //if tempPos.x would round down
		tempPos.y = floor(tempPos.y);
	}
	else {
		tempPos.y = ceil(tempPos.y);
	}
	return tempPos;
}