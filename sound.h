#ifndef sound
#define sound
#include <SDL_mixer.h>

extern Mix_Chunk* moveSound;
extern Mix_Chunk* winSound;
extern Mix_Chunk* loseSound;
extern Mix_Music* bgMusic;
void initSDL_mixer();
#endif
