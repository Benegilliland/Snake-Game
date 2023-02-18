#include "engine.h"

int main(int argc, char* argv[]) {
	const int window_width = 1500;
	const int window_height = 900;
	const int board_width = 300;
	const int board_height = 200;
	const int snake_starting_size = 5;
	const int max_framerate = 300; // Set to 0 to remove framerate limit
	const bool loadGUI = true;
	const bool increase_framerate = false; // Whether to increase the framerate limit (game speed) every time food is eaten
	const control_method control = control_method::computer;

	engine Snake(window_width, window_height, board_width, board_height, snake_starting_size, max_framerate, loadGUI, increase_framerate, control);
	Snake.run_game();

	return 0;
}

// Bug: for the first few seconds, input is usually ignored