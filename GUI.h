#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "structs.h"

class GUI {
	const SDL_Color snake_body_colour{ 0, 255, 0 };
	const SDL_Color snake_head_colour{ 0, 255, 0 };
	const SDL_Color food_colour{ 255, 0, 0 };

	const int c_window_width;
	const int c_window_height;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	TTF_Font* _font;

	SDL_Texture* _scoreLabel;
	SDL_Rect _scoreLabelSize;

	SDL_Texture* _scoreValue;
	SDL_Rect _scoreValueSize;

	SDL_Rect _food;
	
	std::vector<SDL_Rect> _snakeBody;
	SDL_Rect _snakeHead;

	SDL_Point _squareSize;

public:
	GUI(int window_width, int window_height, const int board_width, const int board_height);
	~GUI();
	void draw();
	player_move get_input();
	void update_food(point foodPos);
	void move_snake(size_t tail, point tailPos, point headPos);
	void grow_snake(size_t tail, point tailPos);
	void restart(std::vector<point> body, point head);
	void update_score(int score);
};