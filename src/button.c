#include <SDL3/SDL.h>
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

    SDL_RenderDebugText(pRenderer, x, y, pButton->name);
}

bool buttonPressed () {
    
}

