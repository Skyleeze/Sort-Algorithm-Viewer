#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    bool running;
} App ;

App* createApp(char* title, int w, int h);

void destroyApp(App* pApp);

int initApp(App* pApp);

void processKeyDown(App* pApp, SDL_KeyboardEvent key);

void processKeyUp(App* pApplication, SDL_KeyboardEvent key);

void processAppEvent(App* pApp);

int quitApp(App* pApp);

void renderApp(App* pApp, void (*render)());

int updateApp(App* pApp, void (*update)(), void (*render)());

void runApp(App* pApp,void (*start)(), void (*update)(), void (*render)());

#endif // APPLICATION_H