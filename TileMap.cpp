#include "TileMap.h"

TileMap::TileMap() {}

void TileMap::load(const std::vector<std::vector<int>>& tiles, const AssetManager<Textures::Game::ID, sf::Texture>& textures) {
	_predraw.create(1280, 960);
	_tiles = tiles;

	_lowers = textures.get(Textures::Game::ID::Lowers);
	_background = textures.get(Textures::Game::ID::Background);

	sf::Vector2u mapSize{ _tiles.size() * 64, _tiles[0].size() * 64 };
	auto windowSize = _predraw.getSize();

	sf::Vector2f position = { (windowSize.x - mapSize.x) / 2.f, (windowSize.y - mapSize.y) / 2.f + 100 };

	_pos = position;

	_states.transform.translate(position);

	_predraw.clear(sf::Color(69, 173, 233));

	sf::Sprite bg;
	bg.setTexture(textures.get(Textures::Game::ID::GameBackground));

	_predraw.draw(bg);

	for (size_t i = 0; i < _tiles.size(); ++i) {
		for (size_t j = 0; j < _tiles[i].size(); ++j) {
			sf::Sprite sprite;
			switch (_tiles[i][j]) {
			case -1: {
				continue;
				break;
			}
			case 0: {
				sprite.setTexture(_lowers);
				break;
			}
			case 1: {
				sprite.setTexture(_background);
				break;
			}
			default:
				sprite.setTexture(_background);
				break;
			}
			sprite.setPosition(static_cast<float>(j * _tileSize.x), static_cast<float>(i * _tileSize.y));
			_sprites.push_back(sprite);
		}
	}

	for (auto &i : _sprites) {
		_predraw.draw(i, _states);
	}

	_predraw.display();
	_field.setTexture(_predraw.getTexture());

	_states.transform.translate(-position);
}

std::vector<std::vector<int>>& TileMap::getTiles() {
	return _tiles;
}

const std::vector<std::vector<int>>& TileMap::getTiles() const {
	return _tiles;
}

sf::RenderStates TileMap::getStates() const {
	auto copy = _states;
	copy.transform.translate(_pos);
	return copy;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_field, states);
}