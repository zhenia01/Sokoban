#include "SingleplayerState.h"
#include "StateManager.h"
#include "PlayingState.h"
#include <fstream>

SingleplayerState::SingleplayerState(StateManager& manager, const AssetManager<Textures::Game::ID, sf::Texture>& textures) : _manager(manager), _gameTextures(textures) {
	_type = StateType::Singleplayer;
}

SingleplayerState::~SingleplayerState() {
}

void SingleplayerState::draw(sf::RenderTarget& target, sf::RenderStates states) {
	if (_progress[1] == '1') {
		_1.setOutlineColor(sf::Color::Green);
		_1.setOutlineThickness(5.f);
	} else {
		_1.setOutlineColor(sf::Color::Transparent);
		_1.setOutlineThickness(0.f);
	}
	if (_progress[3] == '1') {
		_2.setOutlineColor(sf::Color::Green);
		_2.setOutlineThickness(5.f);
	} else {
		_2.setOutlineColor(sf::Color::Transparent);
		_2.setOutlineThickness(0.f);
	}
	if (_progress[5] == '1') {
		_3.setOutlineColor(sf::Color::Green);
		_3.setOutlineThickness(5.f);
	} else {
		_3.setOutlineColor(sf::Color::Transparent);
		_3.setOutlineThickness(0.f);
	}
	if (_progress[7] == '1') {
		_4.setOutlineColor(sf::Color::Green);
		_4.setOutlineThickness(5.f);
	} else {
		_4.setOutlineColor(sf::Color::Transparent);
		_4.setOutlineThickness(0.f);
	}
	if (_progress[9] == '1') {
		_5.setOutlineColor(sf::Color::Green);
		_5.setOutlineThickness(5.f);
	} else {
		_5.setOutlineColor(sf::Color::Transparent);
		_5.setOutlineThickness(0.f);
	}
	target.draw(_bg, states);
	target.draw(_levels, states);
	target.draw(_newGame, states);
	target.draw(_1, states);
	target.draw(_2, states);
	target.draw(_3, states);
	target.draw(_4, states);
	target.draw(_5, states);
}

void SingleplayerState::update(const sf::Time&) {
}

void SingleplayerState::handleEvent(const sf::Event& event) {
	_1.handleEvent(event);
	_2.handleEvent(event);
	_3.handleEvent(event);
	_4.handleEvent(event);
	_5.handleEvent(event);

	_newGame.handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			_manager.switchTo(StateType::MainMenu);
		}
	}
}

void SingleplayerState::init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {

	std::ifstream in("Assets/save.save");
	std::getline(in, _progress);
	in.close();
	
	_bgTexture = textures.get(Textures::Menu::ID::MenuBackground);
	_bg.setTexture(_bgTexture);

	_levelsTexture = textures.get(Textures::Menu::ID::Levels);
	_levels.setTexture(_levelsTexture);
	_levels.setPosition((window.getSize().x - _levelsTexture.getSize().x) / 2.f, 700.f - _levelsTexture.getSize().y - 20);

	_newGameTexture = textures.get(Textures::Menu::ID::NewGame);
	_newGame.setTexture(_newGameTexture);
	_newGame.setSize(static_cast<sf::Vector2f>(_newGameTexture.getSize()));
	_newGame.setPosition((window.getSize().x - _levelsTexture.getSize().x) / 2.f, 700.f - (_levelsTexture.getSize().y) * 3.f - 20 * 3.f);

	_newGame.setCallBack([&]() mutable {
		_progress = " 0 0 0 0 0";
		std::ofstream out("Assets/save.save");
		out << _progress << '\n';
		for (int i = 0; i < 5; i++) {
			out << '0' << "\n";
		}
		out.close();
		});

	_1texture = textures.get(Textures::Menu::ID::_1);
	_2texture = textures.get(Textures::Menu::ID::_2);
	_3texture = textures.get(Textures::Menu::ID::_3);
	_4texture = textures.get(Textures::Menu::ID::_4);
	_5texture = textures.get(Textures::Menu::ID::_5);

	_1.setTexture(_1texture);
	_2.setTexture(_2texture);
	_3.setTexture(_3texture);
	_4.setTexture(_4texture);
	_5.setTexture(_5texture);

	_1.setSize({ 64.f, 64.f });
	_2.setSize({ 64.f, 64.f });
	_3.setSize({ 64.f, 64.f });
	_4.setSize({ 64.f, 64.f });
	_5.setSize({ 64.f, 64.f });

	_1.setPosition(375.f, 700.f);
	_2.setPosition(375.f + 64 + 46, 700.f);
	_3.setPosition(375.f + (64 + 46) * 2.f, 700.f);
	_4.setPosition(375.f + (64 + 46) * 3.f, 700.f);
	_5.setPosition(375.f + (64 + 46) * 4.f, 700.f);

	_1.setCallBack([&]() {
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, 1, false, _gameTextures)));
		_manager.init(window, textures);
		});
	_2.setCallBack([&]() {
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, 2, false, _gameTextures)));
		_manager.init(window, textures);
		});
	_3.setCallBack([&]() {
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, 3, false, _gameTextures)));
		_manager.init(window, textures);

		});
	_4.setCallBack([&]() {
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, 4, false, _gameTextures)));
		_manager.init(window, textures);

		});
	_5.setCallBack([&]() {
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, 5, false, _gameTextures)));
		_manager.init(window, textures);
		});
}
