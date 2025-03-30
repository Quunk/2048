#include "text.h"
#include <iostream>
void renderText(const string& text, int x, int y, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("font.ttf", 24); // Load font với kích thước 24px
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if (!textSurface) {
        printf("Unable to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("Unable to create texture: %s\n", SDL_GetError());
    } else {
        SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void showGuide() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Tạo texture hoặc vẽ hướng dẫn trực tiếp lên màn hình
    SDL_Color textColor = {0, 0, 0, 255}; // Màu chữ đen
    renderText("Hướng dẫn chơi:", 100, 100, textColor);
    renderText("- Dùng các phím mũi tên để di chuyển các ô số.", 100, 140, textColor);
    renderText("- Khi hai ô có cùng số chạm nhau, chúng sẽ cộng lại.", 100, 180, textColor);
    renderText("- Mục tiêu: Đạt ô 2048 để chiến thắng!", 100, 220, textColor);
    renderText("Nhấn bất kỳ phím nào để thoát", 100, 300, textColor);

    SDL_RenderPresent(renderer);

    // Chờ người chơi nhấn phím để thoát hướng dẫn
    SDL_Event event;
    while (true) {
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                break; // Thoát hướng dẫn
            }
        }
    }
}
