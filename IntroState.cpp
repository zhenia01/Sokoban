#include "IntroState.h"
#include "StateManager.h"

IntroState::IntroState(StateManager& manager) : _manager(manager) {
	_type = StateType::Intro;
}

void IntroState::draw(sf::RenderTarget& target, sf::RenderStates states) {
	target.draw(_background, states);
	target.draw(_spriteAnim, states);
	if (_time >= 7.5f) {
		target.draw(_spaceSprite, states);
	}
}

void IntroState::update(const sf::Time& time) {
	if (_time < 7.5f) {
		_time += time.asSeconds();
		_spriteAnim.move({0, 300 * time.asSeconds()});
	} else {
		_isReady = true;
	}
}

void IntroState::handleEvent(const sf::Event& event) {
	if (isReady()) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				_manager.switchTo(StateType::MainMenu);
			}
		}
	}
}

void IntroState::init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {
	_bgTexture = textures.get(Textures::Menu::ID::IntroBackground);
	_background.setTexture(_bgTexture);

	_spriteAnimTexture = textures.get(Textures::Menu::ID::IntroImage);
	_spriteAnim.setTexture(_spriteAnimTexture);
	_spriteAnim.setPosition((window.getSize().x - _spriteAnimTexture.getSize().x) / 2.f, -static_cast<float>(_spriteAnimTexture.getSize().y));

	_spaceTexture = textures.get(Textures::Menu::ID::PressSpace);
	_spaceSprite.setTexture(_spaceTexture);
	_spaceSprite.setPosition((window.getSize().x - _spaceTexture.getSize().x)/2.f, 700.f);
}

bool IntroState::isReady() const {
	return _isReady;
}
