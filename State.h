#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Resources.h"

enum class StateType {
	MainMenu, 
	Singleplayer,
	Multiplayer,
	Intro,
	Playing,
	Won,
	None,
	Exit
};

class StateManager;
class State {
public:
	State() : _type(StateType::None) {};
	virtual ~State() {};
	
	virtual void init(
		const sf::RenderWindow& window, 
		const AssetManager<Textures::Menu::ID, sf::Texture>& textures) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update(const sf::Time& time) = 0;
protected:
	StateType _type;
};

