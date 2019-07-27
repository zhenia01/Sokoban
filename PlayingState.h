#pragma once
#include "State.h"
#include "TileMap.h"
#include "Player.h"
#include "SpriteButton.h"
#include "WonState.h"
#include <vector>

class StateManager;
class PlayingState :
	public State {
public:
	PlayingState(StateManager& manager, int level, bool isMultiplayer, const AssetManager<Textures::Game::ID, sf::Texture>& textures);
	virtual ~PlayingState();

	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void update(const sf::Time&) override;

	virtual void handleEvent(const sf::Event&);

	void init(const sf::RenderWindow& window, const AssetManager<Textures::Menu::ID, sf::Texture>& textures);

private:

	bool check();

private:

	TileMap _map;
	Player _players;

	StateManager& _manager;
	
	sf::Sprite _timeSprite;
	sf::Texture _timeTexture;
	
	sf::Sprite _bestSprite;
	sf::Texture _bestTexture;
	GUI::Label _bestLabel;
	float _best = 0.f;

	sf::Texture _backTexture;
	GUI::SpriteButton _back;

	sf::Texture _restartTexture;
	GUI::SpriteButton _restart;

	const AssetManager<Textures::Game::ID, sf::Texture>& _textures;

	int  _level;
	bool _isMultiplayer;

	std::shared_ptr<WonState> _ptr;

	sf::Time _time;

	GUI::Label _timeLabel;
	sf::Font _font;
};
