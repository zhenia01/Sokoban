#pragma once
#include "State.h"

#include "GUI.h"
#include "AssetManager.h"
#include "Resources.h"

#include <SFML\Graphics.hpp>

class StateManager;
class IntroState :
	public State {
public:
	IntroState(StateManager& manager);
	virtual ~IntroState() = default;

	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(const sf::Time& time) override;

	virtual void handleEvent(const sf::Event& event);

	bool isReady() const;

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);

private:
	sf::Sprite _spaceSprite;
	sf::Texture _spaceTexture;

	sf::Sprite _background;
	sf::Texture _bgTexture;

	sf::Sprite _spriteAnim;
	sf::Texture	_spriteAnimTexture;

	float _time = 0.0f;

	bool _isReady = false;

	StateManager& _manager;
};

