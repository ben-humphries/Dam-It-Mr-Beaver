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
	if (!levelTexture.loadFromFile(fileDir)) {
		printf("Couldn't load level texture");
	}

	tileSize = levelTexture.getSize().x / numTiles;

	for (int i = 0; i < numTiles; i++) {
		sf::Sprite s;
		s.setTexture(levelTexture);
		s.setTextureRect(sf::IntRect(numTiles * i % tileSize, numTiles * i / tileSize, tileSize, tileSize));
		s.setOrigin(tileSize / 2, tileSize / 2);
		tiles.push_back(s);
	}
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	sf::Vector2f playerPosition = player->getPosition();
	printf("%d", tileSize);
	for (int i = 0; i < tiles.size(); i++) {
		sf::Vector2f tilePosition = tiles[i].getPosition();
		if (tilePosition.x - tileSize / 2 < playerPosition.x && playerPosition.x < tilePosition.x + tileSize / 2 &&
			tilePosition.y - tileSize / 2 < playerPosition.y && playerPosition.y < tilePosition.y + tileSize / 2) {
			target.draw(tiles[i], states);
		}
	}
}
