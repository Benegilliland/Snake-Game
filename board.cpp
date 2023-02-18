#include "board.h"

board::board(const int board_width, const int board_height) : c_board_width(board_width), c_board_height(board_height) {
	for (int i = 0; i < c_board_width; i++) {
		_board.push_back(std::vector<board_value>(c_board_height));
	}
	reset();
}

void board::reset() {
	for (int i = 0; i < c_board_width; i++) {
		std::fill(_board[i].begin(), _board[i].end(), board_value::empty);
	}
}

board_value board::value(const point& p) const {
	return _board[p.x][p.y];
}

void board::setValue(const point& position, board_value val) {
	_board[position.x][position.y] = val;
}

void board::setValue(int x, int y, board_value val) {
	_board[x][y] = val;
}

bool board::canMove(const point& p) const {
	return (p.x >= 0 && p.y >= 0 && p.x < c_board_width && p.y < c_board_height)
		&& (this->value(p) == board_value::empty || this->value(p) == board_value::food);
}

bool board::isEmpty(int x, int y) const {
	return _board[x][y] == board_value::empty;
}