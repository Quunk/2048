#include "2048.h"
#include "graphic.h"
#include "logic.h"

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    initSDL();
    initSDL_mixer();

    loadHighestScore();
    add_Number();
    add_Number();

    bool running = true;


    SDL_Event event;
    while (running) {
        if (!canMove()) {
            handleGameOver();
            Mix_PlayChannel(-1, loseSound, 0); // Phát âm thanh game over
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
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
            if (score > highestScore) {
                highestScore = score;
                saveHighestScore();  // Lưu điểm cao nhất
            }
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            Mix_PlayChannel(-1, winSound, 0); // Phát âm thanh game over
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
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        renderBoard();
        renderTiles();
        renderScore();
        renderButton("4x4", 347, 10, 70, 50, {156,67,68});
        renderButton("5x5", 347, 70, 70, 50, {63,138,158});
        renderButton("6x6", 347, 130, 70, 50, {71,158,63});
        saveHighestScore();
        SDL_RenderPresent(renderer);
    }


    closeSDL();
    closeMixer();
    return 0;
}
