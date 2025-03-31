#include "logic.h"
#include <iostream>


using namespace std;

// Hàm thêm số 2 vào vị trí ngẫu nhiên
void add_Number(int board[4][4]) {
    int emptyTiles[4 * 4][2], count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
//điều kiện thắng
bool checkWin(int board[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==2048){return true;}
        }
    }
    return false;
}
//khả năng di chuyển ô số
bool canMove(int board[4][4]) {
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
bool moveLeft(int board[4][4],int score,int highestScore, Mix_Chunk* moveSound) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        int target = 0;
        int lastValue = 0;
        for (int j = 0; j < 4; j++) {
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

bool moveRight(int board[4][4],int score,int highestScore, Mix_Chunk* moveSound) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        int target = 4 - 1;
        int lastValue = 0;
        for (int j = 4 - 1; j >= 0; j--) {
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

bool moveUp(int board[4][4],int score,int highestScore, Mix_Chunk* moveSound) {
    bool moved = false;
    for (int j = 0; j < 4; j++) { // Duyệt từng cột
        int target = 0;
        int lastValue = 0;
        for (int i = 0; i < 4; i++) {
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

bool moveDown(int board[4][4],int score,int highestScore, Mix_Chunk* moveSound) {
    bool moved = false;
    for (int j = 0; j < 4; j++) { // Duyệt từng cột
        int target = 4 - 1;
        int lastValue = 0;
        for (int i = 4 - 1; i >= 0; i--) {
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
