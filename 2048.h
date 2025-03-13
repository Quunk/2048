#ifndef graphic
#define graphic
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
##include <utility>

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int GRID_SIZE = 4;
const int CELL_SIZE = 90;
const int PADDING = 10;

extern int board[GRID_SIZE][GRID_SIZE];

void add_Number();
bool checkWin();
bool canMove();
bool moveLeft();
bool moveRight();
bool moveUp();
bool moveDown();
void handleInput(SDL_Event& event);

#endif
