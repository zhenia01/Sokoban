#pragma once
#include "State.h"

#include "GUI.h"
#include "AssetManager.h"
#include "Resources.h"

#include <SFML\Graphics.hpp>

class StateManager;
class MainMenuState :
	public State {
public:
	MainMenuState(StateManager& manager);
	virtual ~MainMenuState();

	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(const sf::Time&) override {};

	virtual void handleEvent(const sf::Event&);

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);

private:
	GUI::SpriteButton _singleSprite;
	sf::Texture _singleTexture;

	GUI::SpriteButton _multiSprite;
	sf::Texture _multiTexture;

	GUI::SpriteButton _exitSprite;
	sf::Texture _exitTexture;

	sf::Sprite _bgSprite;
	sf::Texture _bgTexture;

	StateManager& _manager;
};

