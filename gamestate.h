#pragma once
#include "structs.h"
#include "board.h"
#include "snake.h"

struct gamestate {
	board _board;
	snake _snake;
	point _food;

	gamestate(const int board_width, const int board_height) : _board(board_width, board_height) {}
};