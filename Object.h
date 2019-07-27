#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

enum class ObjectType {
	Diver,
	Web,
	TrashWeb,
	Trash,
	Map, 
	Lowers,
	Background
};
class Object : public sf::Drawable{
public:

	Object(ObjectType type);

	void setTexture(const sf::Texture& texture);

	sf::Texture& getTexture();
	const sf::Texture& getTexture() const;

	void setPosition(const sf::Vector2f& pos);

	void setMapPosition(sf::Vector2i pos);
	void setMapPosition(int x, int y);

	sf::Vector2i getMapPosition() const;

	sf::Vector2f getPosition() const;

	ObjectType getType() const;

	void operator +=(const sf::Vector2i& move);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	ObjectType _type;

protected:
	sf::Vector2f _position;
	sf::Vector2i _mapPosition;
	sf::Texture _texture;
	sf::Sprite _sprite;

	const sf::Vector2f _size;
};

