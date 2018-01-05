#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

static class Level : public sf::Drawable
{
public:
	Level(Player * player);
	~Level();

	static enum LevelName {
		FOREST,
		ISLAND,
		MOUNTAIN
	};

	void load(LevelName levelName);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	sf::Texture levelTexture;
	std::vector<sf::Sprite> tiles;
	int tileSize;

	Player * player;

};

