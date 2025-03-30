#ifndef graphic
#define graphic
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

extern int board[GRID_SIZE][GRID_SIZE];

//Tạo cửa sổ
extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Sound
extern Mix_Chunk* moveSound;
extern Mix_Chunk* winSound;
extern Mix_Chunk* loseSound;
extern Mix_Music* bgMusic;

//background
extern SDL_Texture* backgroundTexture;
SDL_Texture* loadBackground(const std::string& path, SDL_Renderer* renderer);

//Logic
void add_Number();
bool checkWin();
bool canMove();
bool moveLeft();
bool moveRight();
bool moveUp();
bool moveDown();
void handleMouseClick(int x, int y);
void handleInput(SDL_Event& event);

//Score
extern int score;
extern int highestScore;
extern int highScore;
extern int previousHighScore; // Lưu điểm cao nhất của các lần thắng trước
void loadHighestScore();
void saveHighestScore();

//vẽ bảng
extern TTF_Font* font;
SDL_Texture* loadTexture(const string& path);
void initSDL();
SDL_Color getTileColor(int value);
void renderTiles();
void renderBoard();

//Menu
void renderGameOver();
void renderWIN();
void renderScore();
void whenGameOver();
void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color);

void closeSDL();

#endif
