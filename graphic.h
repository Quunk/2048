#ifndef graphic
#define graphic

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 427;
const int SCREEN_HEIGHT = 618;

// vị trí của bảng
const int BOARD_X = 9;
const int BOARD_Y = 200;

// cửa số SDL
extern SDL_Window* window;
extern SDL_Renderer* renderer;
// tạo font chữ
extern TTF_Font* font;
void renderText(const string& text, int x, int y, SDL_Color color);
// background
extern SDL_Texture* backgroundTexture;
SDL_Texture* loadBackground(const string& path, SDL_Renderer* renderer);
void renderImage(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);
// khởi tạo SDL
void initSDL();
// tạo màu và vẽ ô số
SDL_Color getTileColor(int value);
void renderTiles();
// vẽ bảng
void renderBoard();
void closeSDL();
// vẽ nút
void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color);
// vẽ menu khi kết thúc
void renderGameOver();
void renderWIN();
// hiện điểm
void renderScore();

#endif

