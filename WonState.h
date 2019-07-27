#pragma once
#include "State.h"

#include "GUI.h"
#include "AssetManager.h"
#include "Resources.h"
#include "WonState.h"

#include <SFML\Graphics.hpp>

class StateManager;
class WonState :
	public State {
public:
	WonState(StateManager& manager, bool isMultiplayer, size_t level, const AssetManager<Textures::Game::ID, sf::Texture>& textures);
	virtual ~WonState();

	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(const sf::Time&) override {};

	virtual void handleEvent(const sf::Event&);

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);
private:
	
	sf::Sprite _bgSprite;
	sf::Texture _bgTexture;

	sf::Texture _levelsTexture;
	GUI::SpriteButton _levels;
	
	sf::Texture _nextTexture;
	GUI::SpriteButton _next;

	StateManager& _manager;

	bool _isMultiplayer;
	size_t _level;

	const AssetManager<Textures::Game::ID, sf::Texture>& _gameTextures;
};


