#pragma once

#include "TileMap.h" 
#include "Objects.h"
#include "SFML/Graphics.hpp"
#include <stack>

struct Prev {
	std::pair<sf::Vector2i, int> next;
	std::pair<sf::Vector2i, int> pull;

	sf::Vector2i diver;
	Diver::Direction dir = Diver::Direction::Up;
	size_t num = 0;
};

class Player :
	public sf::Drawable{

public:
	Player(std::vector<std::vector<int>>& tiles, bool isMultiplayer);

	void handleEvent(const sf::Event& event);

	void setPlayer1Textures(const sf::Texture& up, const sf::Texture& down, const sf::Texture& left, const sf::Texture& right);
	void setPlayer2Textures(const sf::Texture& up, const sf::Texture& down, const sf::Texture& left, const sf::Texture& right);
	void setTrashWebTextures(const sf::Texture& trash, const sf::Texture& web, const sf::Texture& trashWeb);

	void clear();

	void back();

private:
	void moveLeft(size_t num);
	void moveRight(size_t num);
	void moveUp(size_t num);
	void moveDown(size_t num);

	bool isPulling(const sf::Vector2i& dist, size_t num);
	int canGo(const sf::Vector2i& move, size_t num);
	void move(const sf::Vector2i& dist, size_t num);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update();


private:

	sf::Vector2u _tileSize;

	std::vector<std::vector<int>>& _tiles;

	sf::Texture _diver1Up;
	sf::Texture _diver1Down;
	sf::Texture _diver1Left;
	sf::Texture _diver1Right;	
	
	sf::Texture _diver2Up;
	sf::Texture _diver2Down;
	sf::Texture _diver2Left;
	sf::Texture _diver2Right;

	sf::Texture _trash;
	sf::Texture _web;
	sf::Texture _trashWeb;

	bool _isMultiplayer = false;

	std::vector<Diver> _divers;
	std::list<std::unique_ptr<Object>> _objectList;

	std::stack<Prev> _stack;

};