#include "Object.h"

Object::Object(ObjectType type) : _size({ 64, 64 }), _type(type) {}

void Object::setTexture(const sf::Texture& texture) {
	_texture = texture;
	_sprite.setTexture(texture);
}

sf::Texture& Object::getTexture() {
	return _texture;
}

const sf::Texture& Object::getTexture() const {
	return _texture;
}

void Object::setPosition(const sf::Vector2f& pos) {
	_position = pos;
	_sprite.setPosition(pos);
}

void Object::setMapPosition(sf::Vector2i pos) {
	_mapPosition = pos;
}

void Object::setMapPosition(int x, int y) {
	_mapPosition = { x, y };
}

sf::Vector2i Object::getMapPosition() const {
	return _mapPosition;
}

sf::Vector2f Object::getPosition() const {
	return _position;
}

ObjectType Object::getType() const {
	return _type;
}

void Object::operator+=(const sf::Vector2i& move) {
		_mapPosition += move;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}
