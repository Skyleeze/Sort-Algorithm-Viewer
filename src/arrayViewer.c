#include "../include/application.h"
#include "../include/insertionSort.h"
#include "../include/quickSort.h"
#include "../include/button.h"



#include <SDL3/SDL.h>
#include "time.h"
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>

int WIDTH = 1280;
int HEIGH = 720;

int renderDelay = 12; // Put enough delay to not have rendering problem

SDL_Texture* texture;
SDL_Texture* clearTexture;

SDL_FRect** rects;

Button** pButtons;
int nbButtons = 3;


int* liste;

int nbElem;
App* pApp;

int state = 2;
/* 
0 : Menu
1 : Insertion Sort
2 : Quick Sort
*/


Uint32 createColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    return ((Uint32) a << 24) | ((Uint32) b << 16) | ((Uint32) g << 8) | (Uint32) r;
}


int* genRandomIntArray(int taille) {
    int* tab = malloc(sizeof(int)*taille);
    for (int i = 0; i<taille; i++) {
        tab[i] = rand() % HEIGH;
    }
    return tab;
}

SDL_Texture* initTexture(SDL_Renderer* pRenderer, Uint32 color) {
    SDL_Surface* pSurface = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA32);
    SDL_FillSurfaceRect(pSurface, NULL, color);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    return pTexture;
}


void initRects() {
    rects = SDL_malloc(sizeof(SDL_FRect)*nbElem);
    for (int i = 0; i<nbElem;i++) {
        SDL_FRect* rect = SDL_malloc(sizeof(SDL_FRect));
        rect->w = 1;
        rect->h = 1;
        rect->x = -1;
        rect->y = -1;
        rects[i] = rect;
    }
}

void showArray() {
    for (int i = 0; i<nbElem;i++) {
        rects[i]->x = i;
        rects[i]->y = liste[i];
        rects[i]->h = HEIGH-liste[i];

        SDL_RenderTexture(pApp->pRenderer, texture,NULL,rects[i]);
    }
} 


void clearVerticalLine(int* x) {
    int i = (int
    )(x-liste);
    rects[i]->x = i;
    rects[i]->y = 0;
    rects[i]->h = HEIGH;


    SDL_RenderTexture(pApp->pRenderer, clearTexture,NULL,rects[i]);
    
}



void renderArray() {
    SDL_SetRenderDrawColor(pApp->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pApp->pRenderer);
    showArray();
    SDL_RenderPresent(pApp->pRenderer);
    SDL_Delay(renderDelay);
}

void initButtons() {
    pButtons = malloc(sizeof(Button)*3);
    char* buttonsLabel[] = {"Insertion Sort", "Quick Sort", "Quit"};
    for (int i = 0; i<nbButtons;i++) {
        Button*pButton = malloc(sizeof(Button));
        pButton->name = buttonsLabel[i];
        pButtons[i] = pButton;
    }  
}


void renderQuickSort(int* a, int* b, bool show) {
    int iA = (int)(a-liste);
    int iB = (int)(b-liste);

    clearVerticalLine(a);
    clearVerticalLine(b);

    rects[iA]->x = iA;
    rects[iA]->y = liste[iA];
    rects[iA]->h = HEIGH-liste[iA];

    rects[iB]->x = iB;
    rects[iB]->y = liste[iB];
    rects[iB]->h = HEIGH-liste[iB];

    SDL_RenderTexture(pApp->pRenderer, texture,NULL,rects[iA]);
    SDL_RenderTexture(pApp->pRenderer, texture,NULL,rects[iB]);

    if (show) {
        
        SDL_RenderPresent(pApp->pRenderer);
        SDL_Delay(renderDelay);
    }

}

void start() {
    texture = NULL;
    clearTexture = NULL;
    srand(time(NULL));

    nbElem = WIDTH;

    initRects(); 

    liste = genRandomIntArray(nbElem);
    texture = initTexture(pApp->pRenderer, createColour(155,0,155,255));
    clearTexture = initTexture(pApp->pRenderer, createColour(0, 0, 0, 255));

    initButtons();

    //renderArray();
    //quickSort(liste, nbElem, renderQuickSort); 
    //triInsertion(liste, nbElem, renderArray);
}

void updateMenu() {

}

void updateInsertion() {
    renderArray();
    triInsertion(liste, nbElem, renderArray);
    pApp->running = false;
}

void updateQuickSort() {
    renderArray();
    quickSort(liste, nbElem, renderQuickSort); 
    pApp->running = false;

}


void update() {
    switch (state) {
        case 0:
            updateMenu();
        break;
        case 1:
            updateInsertion();
        break;
        case 2:
            updateQuickSort();
        break;
    }
    
}


void renderMenu() {
    SDL_SetRenderDrawColor(pApp->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pApp->pRenderer);
    for (int i = 0; i<nbButtons;i++) {
        drawButton(pApp->pRenderer,pButtons[i], WIDTH/2,HEIGH/nbButtons, WIDTH/8, HEIGH/8);

    }
    SDL_RenderPresent(pApp->pRenderer);

}

void renderInsertion() {
}

void render() {
    switch (state) {
        case 0:
            renderMenu();
        break;
        case 1:
        break;
        case 2:
        break;
    }
    
}
int main() {
    pApp = createApp("ArrayViewer", WIDTH, HEIGH);


    runApp(pApp,start,update,render);
    
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(clearTexture);
    free(liste);
    destroyApp(pApp);
    
    return 0;
}