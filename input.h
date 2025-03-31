#ifndef input
#define input

#include <SDL.h>
#include <cstdlib>
#include <SDL_mixer.h>

void handleMouseClick(int x, int y, int board[4][4],int score,int highestScore);
void handleInput(SDL_Event& event,int board[4][4],int score,int highestScore, Mix_Chunk* moveSound);
#endif // input

