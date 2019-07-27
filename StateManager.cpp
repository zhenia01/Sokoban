#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow& window) : _current(StateType::Intro), _window(window) {

}

void StateManager::switchTo(const StateType& type) {
	_current = type;
}

void StateManager::remove(const StateType& type) {
	_map.erase(type);
}

void StateManager::addState(const StateType& type, std::shared_ptr<State> ptr) {
		_map.insert_or_assign(type, ptr);
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) {
	_map[_current]->draw(target, states);
}

void StateManager::update(const sf::Time& time) {
	if (_current == StateType::Exit) {
		_window.close();
		switchTo(StateType::Intro);
	} else {
		_map[_current]->update(time);
	}
}

void StateManager::processEvents(const sf::Event& event) {
	_map[_current]->handleEvent(event);
}

void StateManager::initAll(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {
	for (auto& i : _map) {
		i.second->init(window, textures);
	}
}

void StateManager::init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {
	_map[_current]->init(window, textures);
}
