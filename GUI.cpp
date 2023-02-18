#include "GUI.h"
#include <iostream>
#include <string>

GUI::GUI(int window_width, int window_height, const int board_width, const int board_height) : c_window_width(window_width), 
c_window_height(window_height) {
	_squareSize = {(int)(window_width / board_width), (int)(window_height / board_height)};
	window_width = _squareSize.x * board_width;
	window_height = _squareSize.y * board_height;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Couldn't initalise SDL\n";
	}

	_window = NULL;
	_window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	if (_window == NULL) {
		std::cout << "Couldn't create window\n";
	}

	_renderer = NULL;
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL) {
		std::cout << "Couldn't create renderer\n";
	}

	if (TTF_Init() != 0) {
		std::cout << "Couldn't initialise TTF\n";
	}

	_font = NULL;
	_font = TTF_OpenFont("fonts\\OpenSans-Regular.ttf", 100);
	if (_font == NULL) {
		std::cout << "Couldn't load font\n";
	}

	SDL_Surface* tempSurface;
	tempSurface = TTF_RenderText_Solid(_font, "Score: ", SDL_Color{ 255, 255, 255, 255 });
	_scoreLabel = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	_scoreLabelSize = {(int)(window_width * 0.85), (int)(window_height * 0.01), (int)(window_width * 0.06), (int)(window_height * 0.04)};

	tempSurface = TTF_RenderText_Solid(_font, "0", SDL_Color{ 255, 255, 255, 255 });
	_scoreValue = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	_scoreValueSize = { (int)(window_width * 0.915), (int)(window_height * 0.01), (int)(tempSurface->w * window_width * 0.0002), (int)(window_height * 0.04) };
	SDL_FreeSurface(tempSurface);
}

GUI::~GUI() {
	SDL_DestroyTexture(_scoreLabel);
	SDL_DestroyTexture(_scoreValue);
	TTF_CloseFont(_font);
	TTF_Quit();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void GUI::draw() {
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);

	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &_food);

	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	SDL_RenderFillRects(_renderer, _snakeBody.data(), _snakeBody.size());

	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(_renderer, &_snakeHead);

	SDL_RenderCopy(_renderer, _scoreLabel, NULL, &_scoreLabelSize);
	SDL_RenderCopy(_renderer, _scoreValue, NULL, &_scoreValueSize);

	SDL_RenderPresent(_renderer);
}

player_move GUI::get_input() {
	SDL_Event _event;
	SDL_PollEvent(&_event);
	if (_event.type == SDL_KEYDOWN) {
		switch (_event.key.keysym.sym) {
		case SDLK_LEFT:
			return player_move::left;
			break;
		case SDLK_RIGHT:
			return player_move::right;
			break;
		case SDLK_UP:
			return player_move::up;
			break;
		case SDLK_DOWN:
			return player_move::down;
			break;
		case SDLK_ESCAPE:
			exit(0);
		}
	}
	return player_move::none;
}

void GUI::update_food(point foodPos) {
	_food = foodPos.toRect(&_squareSize);
}

void GUI::move_snake(size_t tail, point tailPos, point headPos) {
	_snakeBody[tail] = tailPos.toRect(&_squareSize);
	_snakeHead = headPos.toRect(&_squareSize);
}

void GUI::grow_snake(size_t tail, point tailPos) {
	_snakeBody.insert(_snakeBody.begin() + tail + 1, tailPos.toRect(&_squareSize));
}

void GUI::restart(std::vector<point> body, point head) {
	_snakeBody.clear();
	for (auto& part : body) {
		_snakeBody.push_back(part.toRect(&_squareSize));
	}

	_snakeHead = head.toRect(&_squareSize);
}

void GUI::update_score(int score) {
	SDL_DestroyTexture(_scoreValue);
	SDL_Surface* tempSurface = TTF_RenderText_Solid(_font, std::to_string(score).c_str(), SDL_Color{255, 255, 255, 255});
	_scoreValue = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	_scoreValueSize = { (int)(c_window_width * 0.915), (int)(c_window_height * 0.01), (int)(tempSurface->w * c_window_width * 0.0002), (int)(tempSurface->h * c_window_height * 0.0003) };
	SDL_FreeSurface(tempSurface);
}