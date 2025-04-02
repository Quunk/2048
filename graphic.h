#ifndef graphic
#define graphic

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 427;
const int SCREEN_HEIGHT = 618;
const int CELL_SIZE = 90;
const int PADDING = 10;
const int BOARD_X = 9;
const int BOARD_Y = 200;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

extern SDL_Texture* backgroundTexture;
extern SDL_Texture* smallImage;

SDL_Texture* loadBackground(const string& path, SDL_Renderer* renderer);
void renderImage(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);
void initSDL();
SDL_Color getTileColor(int value);
void renderTiles();
void renderBoard();
void renderText(const string& text, int x, int y, SDL_Color color);
void closeSDL();
void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color);
void renderGameOver();
void renderWIN();
void renderScore();
#endif

