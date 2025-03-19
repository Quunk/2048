#include "2048.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

// Hàm load ảnh số
SDL_Texture* loadTexture(const string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "ERROR: " << path << " SDL_image Error: " << IMG_GetError() << endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Khởi tạo SDL
void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    if (TTF_Init() == -1) {
    cerr << "TTF_Init Error: " << TTF_GetError() << endl;
    }

    window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("arial.ttf", 24);
}

SDL_Color getTileColor(int value) {
    switch (value) {
        case 2: return {238, 228, 218};
        case 4: return {237, 224, 200};
        case 8: return {242, 177, 121};
        case 16: return {245, 149, 99};
        case 32: return {246, 124, 95};
        case 64: return {246, 94, 59};
        case 128: return {237, 207, 114};
        case 256: return {237, 204, 97};
        case 512: return {237, 200, 80};
        case 1024: return {237, 197, 63};
        case 2048: return {237, 194, 46};
        default: return {60, 58, 50};
    }
}
void renderTiles() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int value = board[i][j];

            if (value > 0) {
                SDL_Color color = getTileColor(value);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

                SDL_Rect tile = {
                    BOARD_X + j * (CELL_SIZE + PADDING) + PADDING,
                    BOARD_Y + i * (CELL_SIZE + PADDING) + PADDING,
                    CELL_SIZE,
                    CELL_SIZE
                };
                SDL_RenderFillRect(renderer, &tile);
                // Hiển thị số
                string text = to_string(value);
                SDL_Color textColor = {0, 0, 0};  // Màu đen cho số
                SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

                // Đo kích thước chữ để căn giữa
                int textWidth, textHeight;
                TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
                SDL_Rect textRect = {
                    tile.x + (CELL_SIZE - textWidth) / 2,
                    tile.y + (CELL_SIZE - textHeight) / 2,
                    textWidth,
                    textHeight
                };

                SDL_RenderCopy(renderer, texture, nullptr, &textRect);
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }
}
// Hiển thị bảng game
void renderBoard() {
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_Rect boardRect = {BOARD_X, BOARD_Y, 4 * (CELL_SIZE + PADDING) + PADDING, 4 * (CELL_SIZE + PADDING) + PADDING};
    SDL_RenderFillRect(renderer, &boardRect);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            SDL_Rect cell = {
                BOARD_X + j * (CELL_SIZE + PADDING) + PADDING,
                BOARD_Y + i * (CELL_SIZE + PADDING) + PADDING,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_SetRenderDrawColor(renderer, 205, 192, 180, 255);
            SDL_RenderFillRect(renderer, &cell);
        }
    }
}

void closeSDL() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
