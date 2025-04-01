#ifndef logic
#define logic
#include <SDL_mixer.h>

void add_Number(int board[4][4]);
bool checkWin(int board[4][4]);
bool canMove(int board[4][4]);
bool moveLeft(int board[4][4],int score, int highestScore, Mix_Chunk* moveSound);
bool moveRight(int board[4][4], int score,int highestScore, Mix_Chunk* moveSound);
bool moveUp(int board[4][4], int score, int highestScore, Mix_Chunk* moveSound);
bool moveDown(int board[4][4], int score, int highestScore, Mix_Chunk* moveSound);

#endif // logic

