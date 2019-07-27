#pragma once

#include "State.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <memory>

class StateManager {
public:
	StateManager(sf::RenderWindow& window);

	void switchTo(const StateType& type);

	void remove(const StateType& type);

	void addState(const StateType& type, std::shared_ptr<State> ptr);

	void draw(sf::RenderTarget& target, sf::RenderStates states);

	void update(const sf::Time& time);

	void processEvents(const sf::Event& event);

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);
	void initAll(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);
private:
	std::unordered_map<StateType, std::shared_ptr<State>> _map;
	StateType _current;

	sf::RenderWindow& _window;
};

