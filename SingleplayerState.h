#pragma once
#include "State.h"
#include "Player.h"
#include "SpriteButton.h"
#include "TileMap.h"

class StateManager;
class SingleplayerState :
	public State {
public:
	SingleplayerState(StateManager& manager, const AssetManager<Textures::Game::ID, sf::Texture>& textures);
	virtual ~SingleplayerState();

	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(const sf::Time&) override;

	virtual void handleEvent(const sf::Event&);

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);

private:
	StateManager& _manager;

	sf::Texture _levelsTexture;
	sf::Sprite _levels;

	sf::Texture _newGameTexture;
	GUI::SpriteButton _newGame;

	sf::Texture _1texture;
	GUI::SpriteButton _1;

	sf::Texture _2texture;
	GUI::SpriteButton _2;

	sf::Texture _3texture;
	GUI::SpriteButton _3;

	sf::Texture _4texture;
	GUI::SpriteButton _4;

	sf::Texture _5texture;
	GUI::SpriteButton _5;

	sf::Texture _bgTexture;
	sf::Sprite _bg;

	const AssetManager<Textures::Game::ID, sf::Texture>& _gameTextures;

	std::string _progress = " 0 0 0 0 0";
};

