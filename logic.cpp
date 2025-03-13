#include "2048.h"

int board[GRID_SIZE][GRID_SIZE]={0};

// Hàm thêm số 2 vào vị trí ngẫu nhiên
void add_Number() {
    int emptyTiles[GRID_SIZE * GRID_SIZE][2], count = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        board[emptyTiles[r][0]][emptyTiles[r][1]] = (rand() % 10 < 9) ? 2 : 4;
    }
}
bool checkWin(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==2048){return true;}
        }
    }
    return false;
}

bool canMove() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return true;  // Còn ô trống
            if (j < 3 && board[i][j] == board[i][j + 1]) return true; // Có thể gộp ngang
            if (i < 3 && board[i][j] == board[i + 1][j]) return true; // Có thể gộp dọc
        }
    }
    return false;
}

// Hàm di chuyển
bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < GRID_SIZE; i++) {
        int target = 0;
        int lastValue = 0;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[i][target - 1] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (j != target) {
                        board[i][target] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[i][target];
                    target++;
                }
            }
        }
    }
    return moved;
}

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < GRID_SIZE; i++) {
        int target = GRID_SIZE - 1;
        int lastValue = 0;
        for (int j = GRID_SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[i][target + 1] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (j != target) {
                        board[i][target] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[i][target];
                    target--;
                }
            }
        }
    }
    return moved;
}

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < GRID_SIZE; j++) { // Duyệt từng cột
        int target = 0;
        int lastValue = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[target - 1][j] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (i != target) {
                        board[target][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[target][j];
                    target++;
                }
            }
        }
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < GRID_SIZE; j++) { // Duyệt từng cột
        int target = GRID_SIZE - 1;
        int lastValue = 0;
        for (int i = GRID_SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[target + 1][j] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (i != target) {
                        board[target][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[target][j];
                    target--;
                }
            }
        }
    }
    return moved;
}

// Xử lý sự kiện bàn phím
void handleInput(SDL_Event& event) {
    bool moved = false;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_a: moved = moveLeft(); break;
            case SDLK_d: moved = moveRight(); break;
            case SDLK_w: moved = moveUp(); break;
            case SDLK_s: moved = moveDown(); break;
        }
        if (moved) add_Number();
    }
}
