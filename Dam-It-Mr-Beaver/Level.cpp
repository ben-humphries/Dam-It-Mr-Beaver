#include "Level.h"

const int numTiles = 4;


Level::Level(Player * player)
{
	this->player = player;
}


Level::~Level()
{
}

void Level::load(Level::LevelName levelName) {

	std::string fileDir = "levels/" + std::to_string(levelName) + ".png";
	levelTexture.loadFromFile(fileDir);

	int tileSize = levelTexture.getSize().x / numTiles;

	for (int i = 0; i < numTiles; i++) {
		sf::Sprite s;
		s.setTexture(levelTexture);
		s.setTextureRect(sf::IntRect(numTiles % i * tileSize, numTiles / i * tileSize, tileSize, tileSize));
		s.setOrigin(tileSize / 2, tileSize / 2);
		tiles[i] = s;
	}
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	sf::Vector2f playerPosition = player->getPosition();

}
