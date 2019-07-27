#pragma once

#include "AssetManager.h"
#include "Resources.h"
#include "Player.h"
#include "IntroState.h"
#include "MainMenuState.h"
#include "MultiplayerState.h"
#include "StateManager.h"
#include "SingleplayerState.h"
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	
	void run();

private:
	void render();
	void processEvents();
	void update();

private:
	sf::RenderWindow _window;
	AssetManager<Textures::Game::ID, sf::Texture> _gameTextures;
	AssetManager<Textures::Menu::ID, sf::Texture> _menuTextures;

	StateManager _states;

	sf::Clock _clock;
};

