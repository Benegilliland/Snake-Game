#pragma once
#include "SDL.h"

enum class board_value { empty, snake_body, snake_head, food, wall };
enum class snake_direction : char { left = 0, right = 1, up = 2, down = 3 };
enum class player_move : char { none = -1, left = 0, right = 1, up = 2, down = 3 };
enum class control_method {human, computer};

struct point {
	int x;
	int y;

	SDL_Rect toRect(SDL_Point* size) {
		return { x * size->x, y * size->y, size->x, size->y };
	}

	point left() const {
		return point{ x - 1, y };
	}
	point right() const {
		return { x + 1, y };
	}
	point up() const {
		return { x, y - 1 };
	}
	point down() const {
		return { x, y + 1 };
	}
};