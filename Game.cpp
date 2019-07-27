#include "Game.h"
#include <exception>
#include <iostream>
#include <fstream>

Game::Game() : _window(sf::VideoMode(1280, 960), "Sokoban", sf::Style::Close | sf::Style::Titlebar),
_states(_window){
	try {
		_gameTextures.load(Textures::Game::ID::Background, "Assets/background.png");
		_gameTextures.load(Textures::Game::ID::GameBackground, "Assets/game_bg.jpg");
		_gameTextures.load(Textures::Game::ID::Diver1Down, "Assets/diver1_down.png");
		_gameTextures.load(Textures::Game::ID::Diver1Up, "Assets/diver1_up.png");
		_gameTextures.load(Textures::Game::ID::Diver1Left, "Assets/diver1_left.png");
		_gameTextures.load(Textures::Game::ID::Diver1Right, "Assets/diver1_right.png");
		_gameTextures.load(Textures::Game::ID::Diver2Down, "Assets/diver2_down.png");
		_gameTextures.load(Textures::Game::ID::Diver2Up, "Assets/diver2_up.png");
		_gameTextures.load(Textures::Game::ID::Diver2Left, "Assets/diver2_left.png");
		_gameTextures.load(Textures::Game::ID::Diver2Right, "Assets/diver2_right.png");
		_gameTextures.load(Textures::Game::ID::Lowers, "Assets/lowers.png");
		_gameTextures.load(Textures::Game::ID::TrashWeb, "Assets/trash_web.png");
		_gameTextures.load(Textures::Game::ID::Web, "Assets/web.png");
		_gameTextures.load(Textures::Game::ID::Trash, "Assets/trash.png");

		_menuTextures.load(Textures::Menu::ID::IntroBackground, "Assets/animation_background.png");
		_menuTextures.load(Textures::Menu::ID::IntroImage, "Assets/anim_diver.png");
		_menuTextures.load(Textures::Menu::ID::SinglePlayer, "Assets/single.png");
		_menuTextures.load(Textures::Menu::ID::MultiPlayer, "Assets/multi.png");
		_menuTextures.load(Textures::Menu::ID::MenuExit, "Assets/exit.png");
		_menuTextures.load(Textures::Menu::ID::BackToMenu, "Assets/main.png");
		_menuTextures.load(Textures::Menu::ID::MenuBackground, "Assets/menu_bg.png");
		_menuTextures.load(Textures::Menu::ID::PressSpace, "Assets/space.png");
		_menuTextures.load(Textures::Menu::ID::Back, "Assets/back.png");
		_menuTextures.load(Textures::Menu::ID::Restart, "Assets/restart.png");
		_menuTextures.load(Textures::Menu::ID::Won, "Assets/won.png");
		_menuTextures.load(Textures::Menu::ID::Load, "Assets/load.png");
		_menuTextures.load(Textures::Menu::ID::Save, "Assets/save.png");
		_menuTextures.load(Textures::Menu::ID::NewGame, "Assets/new.png");
		_menuTextures.load(Textures::Menu::ID::Time, "Assets/time.png");
		_menuTextures.load(Textures::Menu::ID::Best, "Assets/best.png");
			
		_menuTextures.load(Textures::Menu::ID::_1, "Assets/1.png");
		_menuTextures.load(Textures::Menu::ID::_2, "Assets/2.png");
		_menuTextures.load(Textures::Menu::ID::_3, "Assets/3.png");
		_menuTextures.load(Textures::Menu::ID::_4, "Assets/4.png");
		_menuTextures.load(Textures::Menu::ID::_5, "Assets/5.png");
		_menuTextures.load(Textures::Menu::ID::Next, "Assets/next.png");
		_menuTextures.load(Textures::Menu::ID::Levels, "Assets/levels.png");
		_menuTextures.load(Textures::Menu::ID::LevelsWhite, "Assets/levelsWhite.png");

	} catch (std::runtime_error & err) {
		std::cerr << err.what() << '\n';
	}
	
	/////////////////////////////////////////////////
	_states.addState(StateType::Intro, std::shared_ptr<IntroState>(new IntroState(_states)));
	_states.addState(StateType::MainMenu, std::shared_ptr<MainMenuState>(new MainMenuState(_states)));
	_states.addState(StateType::Multiplayer, std::shared_ptr<MultiplayerState>(new MultiplayerState(_states, _gameTextures)));
	_states.addState(StateType::Singleplayer, std::shared_ptr<SingleplayerState>(new SingleplayerState(_states, _gameTextures)));
	_states.initAll(_window, _menuTextures);

}

void Game::run() {
	_clock.restart();
	while (_window.isOpen()) {

		processEvents();
		update();
		render();
	}
}

void Game::render() {
	_window.clear(sf::Color::White);

	_states.draw(_window, sf::RenderStates::Default);

	_window.display();
}

void Game::processEvents() {

	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_window.close();
		}

		_states.processEvents(event);
	}
}

void Game::update() {
	_states.update(_clock.getElapsedTime());
	_clock.restart();
}
