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
void Tile::initiateFlowers() {
	sf::Vector2f currentpos = sprite.getPosition();
	currentpos.x /= scaleValue;
	currentpos.y /= scaleValue; //have to divide by scale because getPosition() returns values modified by scale
	cout << currentpos.x << "fwe " << currentpos.y << endl;
	for (float i = currentpos.y; i < currentpos.y + sizeofpicture; i += heightofflower) {
		for (float j = currentpos.x; j < currentpos.x + sizeofpicture; j += widthofflower) {
			flowerLocations[{j, i}] = -1;
			if (rand() % 4 == 0) {
				flowerLocations[{j, i}] = rand() % flowerTypeCount;

			}
		}
	}
}