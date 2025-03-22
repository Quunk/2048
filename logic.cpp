#include "2048.h"

int board[GRID_SIZE][GRID_SIZE]={0};
int score = 0;
int highestScore = 0;
int highScore = 0;
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
                    score += board[i][target - 1]; // Cộng điểm
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
    if (score > highestScore) {
        highestScore = score;
    }
    if (moved) {
    Mix_PlayChannel(-1, moveSound, 0);
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
                    score += board[i][target + 1]; // Cộng điểm
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
    if (score > highestScore) {
        highestScore = score;
    }
    if (moved) {
    Mix_PlayChannel(-1, moveSound, 0);
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
                    score += board[target - 1][j]; // Cộng điểm
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
    if (score > highestScore) {
        highestScore = score;
    }
    if (moved) {
    Mix_PlayChannel(-1, moveSound, 0);
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
                    score += board[target + 1][j];
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
    if (score > highestScore) {
        highestScore = score;
    }
    if (moved) {
    Mix_PlayChannel(-1, moveSound, 0);
    }
    return moved;
}

void handleMouseClick(int x, int y) {
    // Kiểm tra nếu nhấn vào nút Restart
    if (x >= 120 && x <= 300 && y >= 270 && y <= 320) {
        // Reset game
        memset(board, 0, sizeof(board)); // Xóa bảng
        score = 0; // Reset điểm
        add_Number();
        add_Number();
    }
    // Kiểm tra nếu nhấn vào nút Quit
    else if (x >= 120 && x <= 300 && y >= 330 && y <= 380) {
        SDL_Quit(); // Thoát game
        exit(0);
    }
}

void handleInput(SDL_Event& event) {
    bool moved = false;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT: moved = moveLeft(); break;
            case SDLK_RIGHT: moved = moveRight(); break;
            case SDLK_UP: moved = moveUp(); break;
            case SDLK_DOWN: moved = moveDown(); break;
        }
        if (moved) add_Number();
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        handleMouseClick(mouseX, mouseY);
    }
}

void loadHighestScore() {
    FILE* file = fopen("highestscore.txt", "r");
    if (file) {
        fscanf(file, "%d", &highestScore);
        fclose(file);
    }
}

void saveHighestScore() {
    if (score > highestScore) {  // Chỉ lưu nếu đạt điểm cao hơn
        highestScore = score;
        FILE* file = fopen("highestscore.txt", "w");
        if (file) {
            fprintf(file, "%d", highestScore);
            fclose(file);
        }
    }
}

