
#include "sound.h"
#include <iostream>
Mix_Chunk* moveSound = nullptr;
Mix_Chunk* winSound = nullptr;
Mix_Chunk* loseSound = nullptr;
Mix_Music* bgMusic = nullptr;

void initSDL_mixer(){
    // khởi tạo SDL_mixer với MIX_INIT_MP3
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        printf("Mix_Init: Failed to initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME); // Đặt âm lượng tối đa
    moveSound = Mix_LoadWAV("move.wav");
    winSound = Mix_LoadWAV("win.wav");
    loseSound = Mix_LoadWAV("lose.wav");
    bgMusic = Mix_LoadMUS ("music.mp3");
    if (!moveSound||!winSound||!loseSound||!bgMusic) {
        printf("Failed to load effectsound! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else {
        Mix_PlayMusic(bgMusic, -1);
    }
}
