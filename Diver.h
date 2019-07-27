#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>


class Diver :
	public Object{
public:
	Diver();

enum class Direction {
	Up,
	Down,
	Left,
	Right
};
	Direction dir = Direction::Up;

	virtual ~Diver() = default;
};

