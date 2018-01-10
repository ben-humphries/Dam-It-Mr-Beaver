#include "Tile.h"





																									
Tile::Tile(std::string dir) {
	if (!texture.loadFromFile(dir)) {
		printf("Could not load player texture");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(1.0f, 1.0f);
}

Tile::Tile(std::string dir, sf::IntRect rectangle) {
	if (!texture.loadFromFile(dir, rectangle)) {
		printf("NAWEIFNAIWE ");
	}
	else {
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setScale(1.0f, 1.0f);
	}
}

Tile::~Tile() {

}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sprite, states);
}