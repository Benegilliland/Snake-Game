#pragma once
#include "structs.h"

struct snake {
	point _head;
	std::vector<point> _body;
	size_t _tail;
	snake_direction _direction;
};