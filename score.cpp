#include "score.h"
#include <iostream>

void loadHighestScore(int highestScore, int previousHighScore) {
    FILE* file = fopen("highestscore.txt", "r");
    if (file) {
        fscanf(file, "%d", &highestScore);
        previousHighScore = highestScore;  // Lưu lại highestScore trước đó
        fclose(file);
    } else {
        highestScore = 0;
        previousHighScore = 0;
    }
}
//lưu điểm
void saveHighestScore(int highestScore) {
    FILE* file = fopen("highestscore.txt", "w");
    if (file) {
        fprintf(file, "%d", highestScore);
        fclose(file);
    }
}

//khi thua xóa điểm và trả về điểm cao nhất trước
void whenGameOver(int highestScore, int previousHighScore) {
    highestScore = previousHighScore;  // Khôi phục highestScore cũ
    saveHighestScore(highestScore);  // Ghi lại vào file
};


