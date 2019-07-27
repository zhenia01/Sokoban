#include "WonState.h"
#include "StateManager.h"
#include "PlayingState.h"

WonState::WonState(StateManager& manager, bool isMultiplayer, size_t level, const AssetManager<Textures::Game::ID, sf::Texture>& textures) :
	_manager(manager), _isMultiplayer(isMultiplayer),
	_gameTextures(textures), _level(level)
{
	_type = StateType::Won;
}

WonState::~WonState() {
}

void WonState::draw(sf::RenderTarget& target, sf::RenderStates states) {

	target.draw(_bgSprite, states);
	target.draw(_levels, states);
	if (_level < 5) {
		target.draw(_next, states);
	}
}


void WonState::handleEvent(const sf::Event& event) {
	_levels.handleEvent(event);
	if (_level < 5) {
		_next.handleEvent(event);
	}
}

void WonState::init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {

	_bgTexture = textures.get(Textures::Menu::ID::Won);
	_bgSprite.setTexture(_bgTexture);

	_levelsTexture = textures.get(Textures::Menu::ID::LevelsWhite);
	_levels.setTexture(_levelsTexture);
	_levels.setSize(static_cast<sf::Vector2f>(_levelsTexture.getSize()));
	_levels.setPosition(100, 800);
	_levels.setCallBack([&]() {
		_manager.switchTo(
			(_isMultiplayer ? StateType::Multiplayer : StateType::Singleplayer));
		_manager.init(window, textures); 
		});
		
	_nextTexture = textures.get(Textures::Menu::ID::Next);
	_next.setTexture(_nextTexture);
	_next.setSize(static_cast<sf::Vector2f>(_nextTexture.getSize()));
	_next.setPosition(window.getSize().x - 100.f - _nextTexture.getSize().x, 800.f);
	_next.setCallBack([&]() {
		_manager.remove(StateType::Playing);
		_manager.switchTo(StateType::Playing);
		_manager.addState(StateType::Playing, std::shared_ptr<PlayingState>(new PlayingState(_manager, _level+1, _isMultiplayer, _gameTextures)));
		//_manager.init(window, textures);
		_manager.initAll(window, textures);

		});
}