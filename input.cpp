
#include "input.h"
#include "logic.h"
#include "score.h"
// xử lí nhấp chuột
void handleMouseClick(int x, int y, int board[4][4],int score,int highestScore) {
    // Kiểm tra nếu nhấn vào nút Restart
    if (x >= 120 && x <= 300 && y >= 270 && y <= 320) {
        // Reset game
        memset(board, 0, sizeof(board)); // Xóa bảng
        score = 0; // Reset điểm
        add_Number(board);
        add_Number(board);
    }
    // Kiểm tra nếu nhấn vào nút Quit
    else if (x >= 120 && x <= 300 && y >= 330 && y <= 380) {
        saveHighestScore(highestScore); // Lưu highestScore trước khi thoát
        SDL_Quit(); // Thoát game
        exit(0);
    }
}

//xử lí nút di chuyển
void handleInput(SDL_Event& event,int board[4][4],int score,int highestScore, Mix_Chunk* moveSound) {
    bool moved = false;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT: moved = moveLeft(board,score,highestScore,moveSound); break;
            case SDLK_RIGHT: moved = moveRight(board,score,highestScore,moveSound); break;
            case SDLK_UP: moved = moveUp(board,score,highestScore,moveSound); break;
            case SDLK_DOWN: moved = moveDown(board,score,highestScore,moveSound); break;
        }
        if (moved) add_Number(board);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        handleMouseClick(mouseX, mouseY,board,score,highestScore);
    }
}
