#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int x,y,w,h;
} Button ;


Button* createButton (char* name){
    Button* pButton = malloc(sizeof(Button));
    pButton->name = name;
    return pButton;
}
int lenStr(char* str) {
    int i = 0;
    char* p = str;
    while (*p++) {
        i++;
    }
    return i;
}

void drawButton(SDL_Renderer* pRenderer, Button* pButton ,int x, int y, int w, int h ) {
    SDL_SetRenderDrawColor(pRenderer,155,0,155,255);
    SDL_RenderLine(pRenderer, x, y, x+w, y);
    SDL_RenderLine(pRenderer, x, y, x, y+h);
    SDL_RenderLine(pRenderer, x+w, y+h, x, y+h);
    SDL_RenderLine(pRenderer, x+w, y+h, x+w, y); 
    pButton->h = h;
    pButton->w = w;
    pButton->x = x;
    pButton->y = y;
    SDL_RenderDebugText(pRenderer, (x+w/2)-4*lenStr(pButton->name), y+h/2-2, pButton->name);
}

bool buttonPressed (Button* pButton) {
    float mouseX,mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    if (pButton->x < mouseX && pButton->x+pButton->w > mouseX &&
        pButton->y < mouseY && pButton->y+pButton->h > mouseY    
    ) {
        return true;
    }
    return false;
}

