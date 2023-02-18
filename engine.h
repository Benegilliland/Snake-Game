#pragma once
#include <vector>
#include "GUI.h"
#include "structs.h"
#include "board.h"
#include "gamestate.h"
#include "snake.h"

class engine {
	const bool c_increase_framerate;
	const int c_board_width;
	const int c_board_height;	
	const int c_snake_starting_size;
	int _max_framerate;
	
	gamestate _game;

	const control_method c_control;
	GUI* _gui;
	int _score;

public:
	engine(const int window_width, const int window_height, const int board_width, const int board_height, 
		const int snake_starting_size, const int max_framerate, const bool loadGUI, const bool increase_framerate, const control_method control);
	~engine();
	void create_food();
	bool move_snake(); // Returns true if snake has collided with something
	board_value check_collision();
	void restart();
	void run_game();
	void grow_snake();
	void get_direction();
	void limit_framerate(int duration);
};