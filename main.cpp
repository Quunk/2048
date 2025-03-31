#include "logic.h"
#include "graphic.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include <ctime>

int score = 10;
int highestScore = 0;
int previousHighScore = 0 ;
int board[4][4] = {0};

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    initSDL();
    initSDL_mixer();

    loadHighestScore(highestScore, previousHighScore);

    add_Number(board);
    add_Number(board);

    bool running = true;

    SDL_Event event;
    while (running) {
        if (!canMove(board)) {
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            whenGameOver(highestScore, previousHighScore);
            Mix_PlayChannel(-1, loseSound, 0); // Phát âm thanh game over
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
                    handleMouseClick(mouseX, mouseY, board, score, highestScore);
                    break; // Thoát vòng lặp sau khi xử lý click
                }
            }
        }

        if (checkWin(board)) {
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            if (score > highestScore) {
                highestScore = score;
                saveHighestScore(highestScore);  // Lưu điểm cao nhất
            }
            Mix_PlayChannel(-1, winSound, 0); // Phát âm thanh game over
            renderWIN();
            SDL_RenderPresent(renderer);
            saveHighestScore(highestScore);
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
                    handleMouseClick(mouseX, mouseY, board, score,highestScore);
                    break; // Thoát vòng lặp sau khi xử lý click
                }
            }
        }

        // Xử lý sự kiện và vẽ game như bình thường
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event,board,score,highestScore, moveSound);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderBoard();
        renderScore(score, highestScore);
        saveHighestScore(highestScore);
        renderTiles(board);
        SDL_RenderPresent(renderer);
    }


    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(loseSound);
    Mix_CloseAudio();
    return 0;
}
