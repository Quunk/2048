#ifndef main
#define main

#include <ctime>
#include <iostream>
#include <vector>

using namespace std;


extern int GRID_SIZE; // Kích thước bảng
extern int CELL_SIZE ;// kích thước ô số
extern int PADDING ;// khoảng cách các ô

extern vector<vector<int>> board;

extern int score; // điểm hiện tại
extern int highestScore;// điểm cao nhất
extern int previousHighScore;// dùng để lưu điểm cao nhất

#endif
