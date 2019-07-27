#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& manager) : _manager(manager) {
	_type = StateType::MainMenu;
}
MainMenuState::~MainMenuState() {
}


void MainMenuState::handleEvent(const sf::Event& event) {
	_singleSprite.handleEvent(event);
	_multiSprite.handleEvent(event);
	_exitSprite.handleEvent(event);
}

void MainMenuState::init(const sf::RenderWindow&, const AssetManager<Textures::Menu::ID, sf::Texture>& textures) {
	_singleTexture = textures.get(Textures::Menu::ID::SinglePlayer);
	_multiTexture = textures.get(Textures::Menu::ID::MultiPlayer);
	_exitTexture = textures.get(Textures::Menu::ID::MenuExit);
	_bgTexture = textures.get(Textures::Menu::ID::MenuBackground);

	_bgSprite.setTexture(_bgTexture);

	sf::Vector2f buttonSize(362.f, 86.f);

	_singleSprite.setTexture(_singleTexture);
	_singleSprite.setPosition(590.f, 420.f);
	_singleSprite.setSize(buttonSize);
	_singleSprite.setCallBack([this]() {
		_manager.switchTo(StateType::Singleplayer);
		});

	_multiSprite.setTexture(_multiTexture);
	_multiSprite.setPosition(590.f, 570.f);
	_multiSprite.setSize(buttonSize);
	_multiSprite.setCallBack([this]() {
		_manager.switchTo(StateType::Multiplayer);
		});
	
	_exitSprite.setTexture(_exitTexture);
	_exitSprite.setPosition(590.f, 720.f);
	_exitSprite.setSize(buttonSize);
	_exitSprite.setCallBack([&]() {
		_manager.switchTo(StateType::Exit);
		});
}


void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates) {
	target.draw(_bgSprite);
	target.draw(_singleSprite);
	target.draw(_multiSprite);
	target.draw(_exitSprite);
}
