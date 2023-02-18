#include "engine.h"
#include <time.h>
#include <chrono>
#include "AI.h"
#include <iostream>

engine::engine(const int window_width, const int window_height, const int board_width, const int board_height, const int snake_starting_size, 
	const int max_framerate, const bool loadGUI, const bool increase_framerate, const control_method control)
	: _game(board_width, board_height), c_board_width(board_width), c_board_height(board_height), c_snake_starting_size(snake_starting_size),
	_max_framerate(max_framerate), c_increase_framerate(increase_framerate), c_control(control) {

	restart();

	if (loadGUI) {
		_gui = new GUI(window_width, window_height, board_width, board_height);
		_gui->restart(_game._snake._body, _game._snake._head);
	}
	else {
		_gui = NULL;
	}
}

engine::~engine() {
	delete _gui;
}

void engine::restart() {
	_score = 0;
	_game._board.reset();

	const int snake_init_x = (int)(c_board_width / 2);
	const int snake_init_y = (int)(c_board_height / 2);
	_game._snake._body.clear();

	for (int i = 0; i < c_snake_starting_size - 1; i++) {
		_game._board.setValue(snake_init_x, snake_init_y + i, board_value::snake_body);
		_game._snake._body.push_back({ snake_init_x, snake_init_y + i });
	}
	_game._board.setValue(point{ snake_init_x, snake_init_y + c_snake_starting_size - 1 }, board_value::snake_head);
	_game._snake._head = { snake_init_x, snake_init_y + c_snake_starting_size - 1 };
	_game._snake._tail = 0;
	_game._snake._direction = snake_direction::down;

	create_food();
}

void engine::create_food() {
	int x, y;
	bool space_empty = true;
	do {
		x = rand() % c_board_width;
		y = rand() % c_board_height;
		if (_game._board.isEmpty(x,y)) space_empty = true;
		else space_empty = false;
	} while (!space_empty);

	_game._board.setValue( x, y, board_value::food);
	_game._food = { x,y };
	
	if (_gui) _gui->update_food({x,y});
}

bool engine::move_snake() {
	point newTailPos = _game._snake._head;

	_game._board.setValue(_game._snake._head, board_value::snake_body);
	_game._board.setValue(_game._snake._body[_game._snake._tail], board_value::empty);
	_game._snake._body[_game._snake._tail] = _game._snake._head;

	switch (_game._snake._direction) {
	case snake_direction::left:
		_game._snake._head.x -= 1;
		break;
	case snake_direction::right:
		_game._snake._head.x += 1;
		break;
	case snake_direction::up:
		_game._snake._head.y -= 1;
		break;
	case snake_direction::down:
		_game._snake._head.y += 1;
		break;
	}

	board_value collision = check_collision();
	if (collision == board_value::wall || collision == board_value::snake_body) {
		return true;
	}

	if (_gui) _gui->move_snake(_game._snake._tail, newTailPos, _game._snake._head);

	_game._board.setValue(_game._snake._head, board_value::snake_head);
	_game._snake._tail = (_game._snake._tail + 1) % _game._snake._body.size();

	if (collision == board_value::food) {
		_score += 100;
		if (_gui) _gui->update_score(_score);
		grow_snake();
		create_food();
	}

	return false;
}

void engine::grow_snake() {
	if (_max_framerate > 0 && c_increase_framerate) _max_framerate += 1;
	_game._snake._body.insert(_game._snake._body.begin() + _game._snake._tail + 1, _game._snake._body[_game._snake._tail]);
	if (_gui) _gui->grow_snake(_game._snake._tail, _game._snake._body[_game._snake._tail]);
}

void engine::limit_framerate(int duration) {
	if (_max_framerate) {
		int delay = std::max(0, (int)(1000 / _max_framerate - duration));
		SDL_Delay(delay);
	}
}

board_value engine::check_collision() {
	if (_game._snake._head.x < 0 || _game._snake._head.x >= c_board_width)
		return board_value::wall;

	else if (_game._snake._head.y < 0 || _game._snake._head.y >= c_board_height)
		return board_value::wall;

	return _game._board.value(_game._snake._head);

}

void engine::get_direction() {
	player_move plyMove = player_move::none;
	if (_gui && c_control == control_method::human)
		plyMove = _gui->get_input();
	else if (c_control == control_method::computer)
		plyMove = ai_decide_move(_game);

	if (plyMove == player_move::left && _game._snake._direction != snake_direction::right)
		_game._snake._direction = snake_direction::left; 
	else if (plyMove == player_move::right && _game._snake._direction != snake_direction::left)
		_game._snake._direction = snake_direction::right;
	else if (plyMove == player_move::up && _game._snake._direction != snake_direction::down)
		_game._snake._direction = snake_direction::up;
	else if (plyMove == player_move::down && _game._snake._direction != snake_direction::up)
		_game._snake._direction = snake_direction::down;
}

void engine::run_game() {
	bool collision = false;
	_gui->draw();
	//SDL_Delay(5000);
	do {
		auto start = std::chrono::high_resolution_clock::now();

		get_direction();
		collision = move_snake();
		if (_gui) _gui->draw();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		limit_framerate(duration.count());
	} while (!collision);
}