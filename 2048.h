#ifndef graphic
#define graphic
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 427;
const int SCREEN_HEIGHT = 618;
const int GRID_SIZE = 4;
const int CELL_SIZE = 90;
const int PADDING = 10;
const int BOARD_X = 9;
const int BOARD_Y = 200;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

extern int board[GRID_SIZE][GRID_SIZE];

extern int score;
extern int highestScore;

void add_Number();
bool checkWin();
bool canMove();
bool moveLeft();
bool moveRight();
bool moveUp();
bool moveDown();
void handleMouseClick(int x, int y);
void handleInput(SDL_Event& event);

void loadHighestScore();
void saveHighestScore();

SDL_Texture* loadTexture(const string& path);
void initSDL();
SDL_Color getTileColor(int value);
void renderTiles();
void renderBoard();
void renderGameOver();
void renderWIN();
void renderScore();
void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color);

void closeSDL();

#endif
