#include "AI.h"
#include "structs.h"
#include "snake.h"
#include "board.h"

player_move ai_decide_move(const gamestate& game) {
	const point& head = game._snake._head;
	const point& food = game._food;
	const snake_direction& direction = game._snake._direction;
	const board& _board = game._board;

	if (food.x < head.x) { // If we want to go left
		if (direction == snake_direction::right || _board.canMove(head.left()) == false) { // If we can't move left
			if (_board.canMove(head.up()))
				return player_move::up;
			else if (_board.canMove(head.down()))
				return player_move::down;
			else
				return player_move::right;
		}
		else
			return player_move::left;
	}
	else if (food.x > head.x) { // If we want to go right
		if (direction == snake_direction::left || _board.canMove(head.right()) == false) { // If we can't move right
			if (_board.canMove(head.down()))
				return player_move::down;
			else if (_board.canMove(head.up()))
				return player_move::up;
			else
				return player_move::left;
		}
		else
			return player_move::right;
	}
	else if (food.y < head.y) { // If we want to go up
		if (direction == snake_direction::down || _board.canMove(head.up()) == false) { // If we can't move up
			if (_board.canMove(head.left()))
				return player_move::left;
			else if (_board.canMove(head.right()))
				return player_move::right;
			else
				return player_move::down;
		}
		else
			return player_move::up;
	}
	else if (food.y > head.y) { // If we want to go down
		if (direction == snake_direction::up || _board.canMove(head.down()) == false) { // If we can't move down
			if (_board.canMove(head.right()))
				return player_move::right;
			else if (_board.canMove(head.left()))
				return player_move::left;
			else
				return player_move::up;
		}
		else
			return player_move::down;
	}

	return player_move::none;
}