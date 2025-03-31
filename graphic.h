#ifndef graphic
#define graphic
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 427;
const int SCREEN_HEIGHT = 618;
const int CELL_SIZE = 90;
const int PADDING = 10;
const int BOARD_X = 9;
const int BOARD_Y = 200;

//Tạo cửa sổ
extern SDL_Window* window;
extern SDL_Renderer* renderer;

//background
extern SDL_Texture* backgroundTexture;
SDL_Texture* loadBackground(const std::string& path, SDL_Renderer* renderer);

//vẽ bảng
extern TTF_Font* font;
SDL_Texture* loadTexture(const std::string& path);
void initSDL();
SDL_Color getTileColor(int value);
void renderTiles(int board[4][4]);
void renderBoard();

//Menu
void renderGameOver();
void renderWIN();
void renderScore(int score, int highestScore);
void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color);

#endif
