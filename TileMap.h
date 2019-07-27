#pragma once

#include "AssetManager.h"
#include "Resources.h"
#include "Objects.h"
#include <SFML/Graphics.hpp>
#include <memory>

class TileMap :
	public sf::Drawable, public sf::Transformable{
	friend class Player;
public:
	TileMap();

	void load(const std::vector<std::vector<int>>& tiles, const AssetManager<Textures::Game::ID, sf::Texture>& textures);

	std::vector<std::vector<int>>& getTiles();
	const std::vector<std::vector<int>>& getTiles() const;

	sf::RenderStates getStates() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::RenderStates _states;
	sf::Vector2f _pos;

	sf::Vector2u _tileSize = {64, 64};

	std::vector<std::vector<int>> _tiles;

	sf::RenderTexture _predraw;
	sf::Sprite _field;

	std::list<sf::Sprite> _sprites;

	sf::Texture _background;
	sf::Texture _lowers;



};

