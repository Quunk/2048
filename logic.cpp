#include "2048.h"
#include "logic.h"

int GRID_SIZE = 4; // kích thước bảng
int CELL_SIZE = 90;// kích thước ô số
int PADDING = 10;// khoảng cách các ô
vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE, 0));
int score = 0;
int highestScore = 0;
int previousHighScore = 0;

Mix_Chunk* moveSound = nullptr;
Mix_Chunk* winSound = nullptr;
Mix_Chunk* loseSound = nullptr;
Mix_Music* bgMusic = nullptr;

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
        if ( GRID_SIZE == 4){
            board[emptyTiles[r][0]][emptyTiles[r][1]] = (rand() % 10 < 9) ? 2 : 4;
        }
        else if ( GRID_SIZE == 5){
            board[emptyTiles[r][0]][emptyTiles[r][1]] = (rand() % 10 < 7) ? 2 : 4;
        }
        else if ( GRID_SIZE == 6){
            board[emptyTiles[r][0]][emptyTiles[r][1]] = (rand() % 10 < 5) ? 2 : 4;
        }
    }
}
// kiểm tra điều kiện thắng
bool checkWin(){
    if (GRID_SIZE == 4 ){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==2048){return true;}
            }
        }
        return false;
    }
    if (GRID_SIZE == 5 ){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                if(board[i][j]==8192){return true;}
            }
        }
        return false;
    }
    if (GRID_SIZE == 6 ){
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(board[i][j]==32768){return true;}
            }
        }
        return false;
    }
}
// khả năng di chuyển
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
                }
                else {
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
// vùng nhấp chuột
void handleMouseClick(int x, int y) {
    if(checkWin()||!canMove()){
        // Kiểm tra nếu nhấn vào nút Restart
        if (x >= 120 && x <= 300 && y >= 270 && y <= 320) {
            // Reset game
            board.assign(GRID_SIZE, vector<int>(GRID_SIZE, 0)); // Xóa bảng
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
    if(x >= 347 && x<= 417 && y >= 10 && y <= 60){
        GRID_SIZE = 4;
        CELL_SIZE = 90;// kích thước ô số
        PADDING = 10;// khoảng cách các ô
        // Reset game
        board.assign(GRID_SIZE, vector<int>(GRID_SIZE, 0)); // Xóa bảng
        score = 0; // Reset điểm
        add_Number();
        add_Number();
    }
    if(x >= 347 && x<= 417 && y >= 70 && y <= 120){
        GRID_SIZE = 5;
        CELL_SIZE = 70;// kích thước ô số
        PADDING = 10;// khoảng cách các ô
        // Reset game
            board.assign(GRID_SIZE, vector<int>(GRID_SIZE, 0)); // Xóa bảng
            score = 0; // Reset điểm
            add_Number();
            add_Number();
    }
    if(x >= 347 && x<= 417 && y >= 130 && y <= 180){
        GRID_SIZE = 6;
        CELL_SIZE = 57;// kích thước ô số
        PADDING = 10;// khoảng cách các ô
        // Reset game
            board.assign(GRID_SIZE, vector<int>(GRID_SIZE, 0)); // Xóa bảng
            score = 0; // Reset điểm
            add_Number();
            add_Number();
    }
}
// input
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
//lưu điểm
void saveHighestScore() {
    FILE* file = fopen("highestscore.txt", "w");
    if (file) {
        fprintf(file, "%d", highestScore);
        fclose(file);
    }
}
// load lại điểm cao nhất từ file
void loadHighestScore() {
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

// Quay lại điểm cao nhất
void handleGameOver() {
    highestScore = previousHighScore;  // Khôi phục highestScore cũ
    saveHighestScore();  // Ghi lại vào file
}

void initSDL_mixer(){
    // khởi tạo SDL_mixer
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        printf("Mix_Init: Failed to initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_VolumeMusic(100); // Đặt âm lượng tối đa
    moveSound = Mix_LoadWAV("move.wav");
    winSound = Mix_LoadWAV("win.wav");
    loseSound = Mix_LoadWAV("lose.wav");
    bgMusic = Mix_LoadMUS ("muzik_1.mp3");
    Mix_Volume(0,70);
    if (!moveSound||!winSound||!loseSound) {
        printf("Failed to load effectsound! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else if (!bgMusic){
        printf("Failed to load bgMusic! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else {
        Mix_PlayMusic(bgMusic, -1);
    }
}
//giải phóng mixer
void closeMixer(){
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(loseSound);
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
}
