#ifndef logic
#define logic

#include <SDL.h>
#include <cstdlib>
#include <SDL_mixer.h>

extern Mix_Chunk* moveSound;
extern Mix_Chunk* winSound;
extern Mix_Chunk* loseSound;
extern Mix_Music* bgMusic;

void add_Number();
bool checkWin();
bool canMove();
bool moveLeft();
bool moveRight();
bool moveUp();
bool moveDown();

void saveHighestScore();
void handleMouseClick(int x, int y);
void handleInput(SDL_Event& event);
void loadHighestScore();
void handleGameOver();

void initSDL_mixer();
void closeMixer();

#endif // logic
