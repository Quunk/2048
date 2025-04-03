#ifndef logic
#define logic

#include <SDL.h>
#include <cstdlib>
#include <SDL_mixer.h>

// khai báo âm thanh và khởi tạo
extern Mix_Chunk* moveSound;
extern Mix_Chunk* winSound;
extern Mix_Chunk* loseSound;
extern Mix_Music* bgMusic;


void initSDL_mixer();
void closeMixer();

void add_Number();// thêm số
bool checkWin();// kiểm tra điều kiện thắng
bool canMove();// kiểm tra khả năng di chuyển
// các hàm di chuyển
bool moveLeft();
bool moveRight();
bool moveUp();
bool moveDown();
// lưu điểm
void saveHighestScore();
void loadHighestScore();
void handleGameOver();
// input
void handleMouseClick(int x, int y);
void handleInput(SDL_Event& event);

#endif
