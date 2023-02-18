#pragma once
#include "structs.h"
#include <vector>

class board {
	std::vector<std::vector<board_value>> _board;
	const int c_board_width;
	const int c_board_height;

public:
	board(const int board_width, const int board_height);
	void reset();
	board_value value(const point& p) const;
	void setValue(const point& position, board_value val);
	void setValue(int x, int y, board_value val);
	bool canMove(const point& p) const;
	bool isEmpty(int x, int y) const;
};