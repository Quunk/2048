#include "2048.h"

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    initSDL();

    add_Number();
    add_Number();
    bool running = true;
    SDL_Event event;
    while (running) {

        if (checkWin()) {
            cout << "You Win!" << endl;
            break;
        }
        if (!canMove()) {
            cout << "Game over!" << endl;
            break;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderBoard();
        renderTiles();
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    closeSDL();
    return 0;
}
