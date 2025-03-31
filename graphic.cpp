#include "graphic.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
SDL_Texture* backgroundTexture = nullptr;
//load background
SDL_Texture* loadBackground(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface) {
        printf("Không thể load ảnh! SDL_image Error: %s\n", IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture) {
            printf("Không thể tạo texture từ ảnh! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

// Khởi tạo SDL
void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("arial.ttf", 30);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD); // In đậm

    // Load background texture
    backgroundTexture = loadBackground("background.png", renderer);
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
//vẽ các ô số
void renderTiles(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
                std::string text = std::to_string(value);
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
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_SetRenderDrawColor(renderer, 51,177,189, 255);
    SDL_Rect boardRect = {BOARD_X, BOARD_Y, 4 * (CELL_SIZE + PADDING) + PADDING, 4 * (CELL_SIZE + PADDING) + PADDING};
    SDL_RenderFillRect(renderer, &boardRect);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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

//vẽ bảng menu khi kết thúc
void renderGameOver() {
    SDL_Color textColor = {255, 255, 255, 255}; // Màu trắng
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Over!", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {115, 220, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Vẽ nút Restart
    renderButton("Restart", 120, 270, 180, 50, {119, 110, 101});

    // Vẽ nút Quit
    renderButton("Quit", 120, 330, 180, 50, {205, 50, 50});
}

void renderWIN() {
    SDL_Color textColor = {255, 255, 255, 255}; // Màu trắng
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "You Win!", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {130, 220, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Vẽ nút Restart
    renderButton("Restart", 120, 270, 180, 50, {119, 110, 101});

    // Vẽ nút Quit
    renderButton("Quit", 120, 330, 180, 50, {205, 50, 50});
}

void renderButton(const char* text, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect buttonRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_Color textColor = {255, 255, 255};  // Màu chữ trắng
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    TTF_SizeText(font, text, &textWidth, &textHeight);
    SDL_Rect textRect = {
        x + (w - textWidth) / 2,
        y + (h - textHeight) / 2,
        textWidth,
        textHeight
    };

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// hiện điểm
void renderScore(int score, int highestScore) {
    SDL_Color textColor = { 255, 255, 255}; // Màu chữ trắng
    std::string scoreText = "Score: " + std::to_string(score);

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect scoreRect = { 20, 120, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &scoreRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Hiển thị highest score
    std::string highScoreText = "Highest: " + std::to_string(highestScore);
    SDL_Surface* hsSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
    SDL_Texture* hsTexture = SDL_CreateTextureFromSurface(renderer, hsSurface);
    SDL_Rect hsRect = { 20, 150, hsSurface->w, hsSurface->h };
    SDL_RenderCopy(renderer, hsTexture, NULL, &hsRect);
    SDL_FreeSurface(hsSurface);
    SDL_DestroyTexture(hsTexture);
}
