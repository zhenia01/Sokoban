#include	"Player.h"

Player::Player(std::vector<std::vector<int>>& tiles, bool isMultiplayer) : _tiles(tiles), _tileSize({ 64, 64 }), _isMultiplayer(isMultiplayer) {
	_divers.push_back(Diver());
	if (isMultiplayer) {
		_divers.push_back(Diver());
	}
}

void Player::setPlayer1Textures(const sf::Texture& up, const sf::Texture& down, const sf::Texture& left, const sf::Texture& right) {

	_diver1Up = up;
	_diver1Down = down;
	_diver1Left = left;
	_diver1Right = right;

	for (size_t i = 0; i < _tiles.size(); ++i) {
		for (size_t j = 0; j < _tiles[i].size(); ++j) {
			if (_tiles[i][j] == 5) {
				_divers[0].setMapPosition({ static_cast<int>(j), static_cast<int>(i) });
				break;
			}
		}
	}

	update();
	_divers[0].setTexture(_diver1Up);
}

void Player::setPlayer2Textures(const sf::Texture& up, const sf::Texture& down, const sf::Texture& left, const sf::Texture& right) {

	_diver2Up = up;
	_diver2Down = down;
	_diver2Left = left;
	_diver2Right = right;

	for (size_t i = 0; i < _tiles.size(); ++i) {
		for (size_t j = 0; j < _tiles[i].size(); ++j) {
			if (_tiles[i][j] == 5) {
				_divers[1].setMapPosition({ static_cast<int>(j), static_cast<int>(i) });
				break;
			}
		}
	}

	update();
	_divers[1].setTexture(_diver2Up);
}

void Player::setTrashWebTextures(const sf::Texture& trash, const sf::Texture& web, const sf::Texture& trashWeb) {

	_trash = trash;
	_web = web;
	_trashWeb = trashWeb;

	for (size_t i = 0; i < _tiles.size(); ++i) {
		for (size_t j = 0; j < _tiles[i].size(); ++j) {
			switch (_tiles[i][j]) {
			case 2: {
				std::unique_ptr<Trash> temp(new Trash());
				temp->setMapPosition({ static_cast<int>(j), static_cast<int>(i) });
				temp->setTexture(_trash);
				_objectList.push_back(std::move(temp));
				break;
			}
			case 3: {
				std::unique_ptr<Web> temp(new Web());
				temp->setMapPosition({ static_cast<int>(j), static_cast<int>(i) });
				temp->setTexture(_web);
				_objectList.push_back(std::move(temp));
				break;
			}
			case 4: {
				std::unique_ptr<TrashWeb> temp(new TrashWeb());
				temp->setMapPosition({ static_cast<int>(j), static_cast<int>(i) });
				temp->setTexture(_trashWeb);
				_objectList.push_back(std::move(temp));
				break;
			}
			default:
				break;
			}
		}
	}

	update();
}
void Player::clear() {
	_divers.clear();
	_objectList.clear();
	_divers.push_back(Diver());
	if (_isMultiplayer) {
		_divers.push_back(Diver());
	}
}

void Player::back() {
	if (!_stack.empty()) {

		Prev prev = _stack.top();

		_divers[prev.num].setMapPosition(prev.diver);

		if (prev.num == 0) {
			switch (prev.dir) {
			case Diver::Direction::Down:
				_divers[0].setTexture(_diver1Down);
				break;
			case Diver::Direction::Up:
				_divers[0].setTexture(_diver1Up);
				break;
			case Diver::Direction::Left:
				_divers[0].setTexture(_diver1Left);
				break;
			case Diver::Direction::Right:
				_divers[0].setTexture(_diver1Right);
				break;
			default:
				break;
			}
		} else if (_isMultiplayer) {
			switch (prev.dir) {
			case Diver::Direction::Down:
				_divers[1].setTexture(_diver2Down);
				break;
			case Diver::Direction::Up:
				_divers[1].setTexture(_diver2Up);
				break;
			case Diver::Direction::Left:
				_divers[1].setTexture(_diver2Left);
				break;
			case Diver::Direction::Right:
				_divers[1].setTexture(_diver2Right);
				break;
			default:
				break;
			}
		}

		_tiles[prev.next.first.y][prev.next.first.x] = prev.next.second;
		_tiles[prev.pull.first.y][prev.pull.first.x] = prev.pull.second;

		_stack.pop();

		update();
	}
}

void Player::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::Left:
			_divers[0].setTexture(_diver1Left);
			_divers[0].dir = Diver::Direction::Left;
			moveLeft(0);
			break;
		case sf::Keyboard::Right:
			_divers[0].setTexture(_diver1Right);
			_divers[0].dir = Diver::Direction::Right;
			moveRight(0);
			break;
		case sf::Keyboard::Up:
			_divers[0].setTexture(_diver1Up);
			_divers[0].dir = Diver::Direction::Up;
			moveUp(0);
			break;
		case sf::Keyboard::Down:
			_divers[0].setTexture(_diver1Down);
			_divers[0].dir = Diver::Direction::Down;
			moveDown(0);
			break;
		default:
			break;
		}
		
	if (_isMultiplayer) {
		switch (event.key.code) {
		case sf::Keyboard::A:
			_divers[1].setTexture(_diver2Left);
			_divers[1].dir = Diver::Direction::Left;
			moveLeft(1);
			break;

		case sf::Keyboard::D:
			_divers[1].setTexture(_diver2Right);
			_divers[1].dir = Diver::Direction::Right;
			moveRight(1); 
			break;
		case sf::Keyboard::W:
			_divers[1].setTexture(_diver2Up);
			_divers[1].dir = Diver::Direction::Up;
			moveUp(1);
			break;
		case sf::Keyboard::S:
			_divers[1].setTexture(_diver2Down);
			_divers[1].dir = Diver::Direction::Down;
			moveDown(1);
			break;
		default:
			break;
			}
		}
	}
}

void Player::moveLeft(size_t num) {
	move({ -1, 0 }, num);
}

void Player::moveRight(size_t num) {
	move({ 1, 0 }, num);
}

void Player::moveUp(size_t num) {
	move({ 0, -1 }, num);
}

void Player::moveDown(size_t num) {
	move({ 0, 1 }, num);
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	for (auto& i : _objectList) {
		target.draw(*i, states);
	}
	target.draw(_divers[0], states);
	if (_isMultiplayer) {
		target.draw(_divers[1], states);
	}
}

void Player::update() {
	_divers[0].setPosition(static_cast<sf::Vector2f>(
		sf::Vector2u{ _divers[0].getMapPosition().x * _tileSize.x, _divers[0].getMapPosition().y * _tileSize.y }));

	if (_isMultiplayer) {
		_divers[1].setPosition(static_cast<sf::Vector2f>(
			sf::Vector2u{ _divers[1].getMapPosition().x * _tileSize.x, _divers[1].getMapPosition().y * _tileSize.y }));
	}

	_objectList.clear();

	for (size_t i = 0; i < _tiles.size(); ++i) {
		for (size_t j = 0; j < _tiles[i].size(); j++) {
			switch (_tiles[i][j]) {

			case 2: {
				std::unique_ptr<Object> ptr(new Trash());
				ptr->setMapPosition(j, i);
				ptr->setPosition(static_cast<sf::Vector2f>(sf::Vector2u{ j * _tileSize.x, i * _tileSize.y }));
				ptr->setTexture(_trash);
				_objectList.push_back(std::move(ptr));
				break;
			}
			case 3: {
				std::unique_ptr<Object> ptr(new Web());
				ptr->setMapPosition(j, i);
				ptr->setPosition(static_cast<sf::Vector2f>(sf::Vector2u{ j * _tileSize.x, i * _tileSize.y }));
				ptr->setTexture(_web);
				_objectList.push_back(std::move(ptr));
				break;
			}
			case 4: {
				std::unique_ptr<Object> ptr(new TrashWeb());
				ptr->setMapPosition(j, i);
				ptr->setPosition(static_cast<sf::Vector2f>(sf::Vector2u{ j * _tileSize.x, i * _tileSize.y }));
				ptr->setTexture(_trashWeb);
				_objectList.push_back(std::move(ptr));
				break;
			}

			default:
				break;
			}
		}
	}
}


bool Player::isPulling(const sf::Vector2i & dist, size_t num) {

	auto pos = _divers[num].getMapPosition() + dist;
	if (_tiles[pos.y][pos.x] == 2 || _tiles[pos.y][pos.x] == 4) {
		return true;
	}
	return false;
}

int Player::canGo(const sf::Vector2i & move, size_t num) {
	sf::Vector2i newPos = static_cast<sf::Vector2i>(_divers[num].getMapPosition() + move);

	bool lowerBounds = newPos.x >= 0 && newPos.y >= 0;
	bool upperBounds = newPos.x < static_cast<int>(_tiles[0].size()) && newPos.y < static_cast<int>(_tiles.size());

	bool bounds = lowerBounds && upperBounds;

	if (bounds && !isPulling(move, num)) {
		if (_tiles[newPos.y][newPos.x] != 0) {
			return 1;
		}
	} else {
		newPos += move;
		if ((_tiles[newPos.y][newPos.x] != 0 && _tiles[newPos.y][newPos.x] != 2) && _tiles[newPos.y][newPos.x] != 4) {
			if (!_isMultiplayer || (_isMultiplayer && (newPos != _divers[1].getMapPosition() && newPos != _divers[0].getMapPosition()))) {
				return 2;
			}
		}
	}

	return 0;
}

void Player::move(const sf::Vector2i & dist, size_t num) {

	int res = canGo(dist, num);

	if (res > 0) {

		Prev prev;

		prev.num = num;
		prev.dir = _divers[num].dir;

		/////////////////////////////////

		auto diverPos = _divers[num].getMapPosition();

		//prev
		prev.diver = diverPos;


		auto nextPos = diverPos + dist;

		//prev
		prev.next.first = nextPos;

		auto pullPos = nextPos + dist;

		//prev
		prev.pull.first = pullPos;

		auto& nextTile = _tiles[nextPos.y][nextPos.x];

		//prev
		prev.next.second = nextTile;

		auto& pullTile = _tiles[pullPos.y][pullPos.x];

		//prev
		prev.pull.second = pullTile;

		/////////////////////
		if (res == 2) {
			for (auto& i : _objectList) {
				if (i->getMapPosition() == nextPos) {

					switch (nextTile) {

					case 2: { // trash

						switch (pullTile) {

						case 1: case 5: {
							pullTile = 2;
							nextTile = 1;
							break;
						}

						case 3: {
							pullTile = 4;
							nextTile = 1;
							break;
						}

						default:
							break;
						}

						break;
					}

					case 4: { // trashweb

						switch (pullTile) {

						case 1: case 5: {
							pullTile = 2;
							nextTile = 3;
							break;
						}

						case 3: {

							pullTile = 4;
							nextTile = 3;
							break;
						}

						default:
							break;
						}

						break;
					}

					default:
						break;
					}

					break;
				}
			}
		}
		_divers[num] += dist;
		_stack.push(prev);
		update();
	}
}