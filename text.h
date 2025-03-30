#ifndef text
#define text
#include <string>
#include <SDL_ttf.h>
using namespace std;

void renderText(const string& text, int x, int y, SDL_Color color);
void showGuide();

#endif // text
