#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

static class Level : sf::Drawable
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

	Player * player;

};

