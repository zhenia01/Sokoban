#include "PlayingState.h"
#include "StateManager.h"
#include "WonState.h"
#include <fstream>
#include <string>

PlayingState::PlayingState(StateManager& manager,
	int level, bool isMultiplayer,
	const AssetManager<Textures::Game::ID, sf::Texture>& textures) :
	_manager(manager),
	_players(_map.getTiles(), isMultiplayer),
	_textures(textures),
	_level(level),
	_isMultiplayer(isMultiplayer),
	_ptr(new WonState(manager, isMultiplayer, level, textures)) {

	_type = StateType::Playing;

	std::vector<std::vector<int>> map;

	std::ifstream in;
	in.open("Assets/map" + std::string(std::to_string(_level)) + (_isMultiplayer ? "mp.map" : ".map"));

	size_t rows, columns;
	in >> rows;
	in >> columns;

	for (size_t i = 0; i < rows; ++i) {
 		map.push_back(std::vector<int>(columns));
		for (size_t j = 0; j < columns; ++j) {
			int a;
			in >> a;
			map[i][j] = a;
		}
	}

	in.close();

	_map.load(map, _textures);

	_players.setPlayer1Textures(
		_textures.get(Textures::Game::ID::Diver1Up),
		_textures.get(Textures::Game::ID::Diver1Down),
		_textures.get(Textures::Game::ID::Diver1Left),
		_textures.get(Textures::Game::ID::Diver1Right));

	if (_isMultiplayer) {
		_players.setPlayer2Textures(
			_textures.get(Textures::Game::ID::Diver2Up),
			_textures.get(Textures::Game::ID::Diver2Down),
			_textures.get(Textures::Game::ID::Diver2Left),
			_textures.get(Textures::Game::ID::Diver2Right));
	}

	_players.setTrashWebTextures(
		_textures.get(Textures::Game::ID::Trash),
		_textures.get(Textures::Game::ID::Web),
		_textures.get(Textures::Game::ID::TrashWeb));
}

PlayingState::~PlayingState() {
}

void PlayingState::draw(sf::RenderTarget& target, sf::RenderStates states) {
	target.draw(_map, states);
	target.draw(_players, _map.getStates());
	target.draw(_players, _map.getStates());
	target.draw(_restart, states);
	target.draw(_back, states);
	target.draw(_timeSprite, states);
	target.draw(_bestSprite, states);
	if (_best > 0.1f) {
		target.draw(_bestLabel, states);
	}
	target.draw(_timeLabel, states);
}

void PlayingState::update(const sf::Time& time) {
	_time += time;
	std::string minutes = std::to_string(static_cast<int>(_time.asSeconds()) / 60);
	std::string seconds = std::to_string(static_cast<int>(_time.asSeconds()) % 60);

	if (minutes.size() == 1) {
		minutes = "0" + minutes;
	}

	if (seconds.size() == 1) {
		seconds = "0" + seconds;
	}

	_timeLabel.setText(minutes + ":" + seconds);
}

void PlayingState::handleEvent(const sf::Event & event) {

	_players.handleEvent(event);

	if (check()) {
		std::string temp;
		std::ifstream in("Assets/save" + std::string((_isMultiplayer ? "mp.save" : ".save")));
		std::getline(in, temp);

		float arr[5];
		for (int i = 0; i < 5; i++) {
			in >> arr[i];
		}

		in.close();
		temp[(_level - 1) * 2 + 1] = '1';
		std::ofstream out("Assets/save" + std::string((_isMultiplayer ? "mp.save" : ".save")));
		out << temp;

		out << '\n';

		for (int i = 0; i < 5; i++) {
			if (i + 1 == _level) {
				if (_best < 0.1f) {
					out << _time.asSeconds();
				} else if (_best > _time.asSeconds()) {
					out << _time.asSeconds();
				} else {
					out << _best;
				}
			} else {
				out << arr[i];
			}
			out << '\n';
		}

		out.close();

		_manager.switchTo(StateType::Won);
		_manager.addState(StateType::Won, _ptr);
		_manager.remove(StateType::Playing);
		return;
	}

	_back.handleEvent(event);
	_restart.handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			_manager.switchTo(
				(_isMultiplayer ? StateType::Multiplayer : StateType::Singleplayer));
			_manager.remove(StateType::Playing);
		}
	}
}

void PlayingState::init(const sf::RenderWindow & window, const AssetManager<Textures::Menu::ID, sf::Texture> & textures) {

	_ptr->init(window, textures);

	_restartTexture = textures.get(Textures::Menu::ID::Restart);
	_restart.setPosition(20, 20);
	_restart.setTexture(_restartTexture);
	_restart.setSize({ 69, 86 });

	_backTexture = textures.get(Textures::Menu::ID::Back);
	_back.setPosition(_restart.getPosition() + sf::Vector2f{ _restart.getSize().x, 0 } +sf::Vector2f{ 20, 0 });
	_back.setTexture(_backTexture);
	_back.setSize({ 69, 86 });
	_back.setCallBack([this]() mutable {
		_players.back();
		});

	_timeTexture = textures.get(Textures::Menu::ID::Time);
	_timeSprite.setTexture(_timeTexture);
	_timeSprite.setPosition(window.getSize().x / 2.f - _timeTexture.getSize().x / 2.f - 100, 20);

	_bestTexture = textures.get(Textures::Menu::ID::Best);
	_bestSprite.setTexture(_bestTexture);
	_bestSprite.setPosition(window.getSize().x / 2.f - _bestTexture.getSize().x / 2.f + 100, 20);

	_font.loadFromFile("Assets/arial.ttf");
	_timeLabel.setFont(_font);
	_timeLabel.setSize(static_cast<sf::Vector2f>(sf::Vector2u(_timeTexture.getSize().x - 10, _timeTexture.getSize().y / 2 - 10)));
	_timeLabel.setPosition(_timeSprite.getPosition().x + 5, _timeSprite.getPosition().y + _timeTexture.getSize().y / 2);
	_timeLabel.setTextColor(sf::Color(23, 114, 172));
	_timeLabel.setText("00:00");

	std::string temp;
	std::ifstream in("Assets/save" + std::string((_isMultiplayer ? "mp.save" : ".save")));
	std::getline(in, temp);
	for (int i = 1; i <= _level; i++) {
		in >> _best;
	}

	in.close();

	_bestLabel.setFont(_font);
	_bestLabel.setSize(static_cast<sf::Vector2f>(sf::Vector2u(_bestTexture.getSize().x- 10, _bestTexture.getSize().y / 2 - 10)));
	_bestLabel.setPosition(_bestSprite.getPosition().x + 5, _bestSprite.getPosition().y + _bestTexture.getSize().y / 2);
	_bestLabel.setTextColor(sf::Color(23, 114, 172));

	std::string minutes = std::to_string(static_cast<int>(_best) / 60);
	std::string seconds = std::to_string(static_cast<int>(_best) % 60);

	if (minutes.size() == 1) {
		minutes = "0" + minutes;
	}

	if (seconds.size() == 1) {
		seconds = "0" + seconds;
	}

	_bestLabel.setText(minutes + ":" + seconds);

	_restart.setCallBack([this]() mutable {

		_time = sf::Time::Zero;

		std::vector<std::vector<int>> map;

		std::ifstream in;
		in.open("Assets/map" + std::string(std::to_string(_level)) + (_isMultiplayer ? "mp.map" : ".map"));

		size_t rows, columns;
		in >> rows;
		in >> columns;

		for (size_t i = 0; i < rows; ++i) {
			map.push_back(std::vector<int>(columns));
			for (size_t j = 0; j < columns; ++j) {
				int a;
				in >> a;
				map[i][j] = a;
			}
		}

		in.close();

		_players.clear();
		_map.load(map, _textures);

		_players.setPlayer1Textures(
			_textures.get(Textures::Game::ID::Diver1Up),
			_textures.get(Textures::Game::ID::Diver1Down),
			_textures.get(Textures::Game::ID::Diver1Left),
			_textures.get(Textures::Game::ID::Diver1Right));

		if (_isMultiplayer) {
			_players.setPlayer2Textures(
				_textures.get(Textures::Game::ID::Diver2Up),
				_textures.get(Textures::Game::ID::Diver2Down),
				_textures.get(Textures::Game::ID::Diver2Left),
				_textures.get(Textures::Game::ID::Diver2Right));
		}

		_players.setTrashWebTextures(
			_textures.get(Textures::Game::ID::Trash),
			_textures.get(Textures::Game::ID::Web),
			_textures.get(Textures::Game::ID::TrashWeb));
		});
}

bool PlayingState::check() {
	for (auto& i : _map.getTiles()) {
		for (auto j : i) {
			if (j == 2) {
				return false;
			}
		}
	}

	return true;
}
