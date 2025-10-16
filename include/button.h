#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>

typedef struct {
    char* name;
    int x,y,w,h;
} Button ;


Button* createButton (char* name);
void drawButton(SDL_Renderer* pRenderer, Button* pButton ,int x, int y, int w, int h ) ;

bool buttonPressed () ;



#endif // BUTTON_H
 