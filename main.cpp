#include "2048.h"

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    initSDL();

    loadHighestScore();

    add_Number();
    add_Number();

    bool running = true;

    SDL_Event event;
    while (running) {
        if (!canMove()) {
            renderGameOver();
            SDL_RenderPresent(renderer);

            // Chờ người chơi chọn Restart hoặc Quit
            SDL_Event event;
            while (SDL_WaitEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    break;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    handleMouseClick(mouseX, mouseY);
                    break; // Thoát vòng lặp sau khi xử lý click
                }
            }
        }

        if (checkWin()) {
            renderWIN();
            SDL_RenderPresent(renderer);
            saveHighestScore();
            // Chờ người chơi chọn Restart hoặc Quit
            SDL_Event event;
            while (SDL_WaitEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    break;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    handleMouseClick(mouseX, mouseY);
                    break; // Thoát vòng lặp sau khi xử lý click
                }
            }
        }

        // Xử lý sự kiện và vẽ game như bình thường
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderBoard();
        renderScore();
        renderTiles();
        SDL_RenderPresent(renderer);
    }


    closeSDL();
    return 0;
}
