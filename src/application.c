#include <SDL3/SDL_events.h>
#include <stdbool.h>


#include <SDL3/SDL.h>


typedef struct {
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    bool running;
    bool mousePressed;
} App ;

App* createApp(char* title, int w, int h) {
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL3 Failed Initialization");
        return  NULL;
    }



    App *pApp = SDL_malloc(sizeof(App));
    if (!pApp) {
        SDL_free(pApp);
        SDL_Quit();
        SDL_Log("Memory Allocation Failed");
        return  NULL;
    }



    pApp->pWindow = SDL_CreateWindow(title, w, h, (SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN));
    if (!pApp->pWindow) {
        SDL_DestroyWindow(pApp->pWindow);
        SDL_Quit();
        SDL_Log("Windows Creation Failed");
        return  NULL;
    }

    pApp->pRenderer = SDL_CreateRenderer(pApp->pWindow, NULL);
    if (!pApp->pRenderer) {
        SDL_DestroyWindow(pApp->pWindow);
        SDL_free(pApp);
        SDL_Quit();
        SDL_Log("Renderer Creation Failed");
        return NULL;
    }

    pApp->running = false;

    return pApp;
}


void destroyApp(App* pApp) {
    if (!pApp) {
        return;
    }

    SDL_DestroyWindow(pApp->pWindow);
    SDL_DestroyRenderer(pApp->pRenderer);


    SDL_free(pApp);
    SDL_Quit();
}



int initApp(App* pApp) {

    SDL_ShowWindow(pApp->pWindow);

    pApp->running = true;
    return 0;
}

void processKeyDown(App* pApp, SDL_KeyboardEvent key) {
    switch (key.scancode) {
        case SDL_SCANCODE_ESCAPE:
            pApp->running = false;
        break;
    }
}

void processKeyUp(App* pApplication, SDL_KeyboardEvent key) {

}


void processAppEvent(App* pApp) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                pApp->running = false;
            break;
            
            case SDL_EVENT_KEY_DOWN:
                processKeyDown(pApp, event.key);
            break;
            
            case SDL_EVENT_KEY_UP:
                processKeyUp(pApp,  event.key);
            break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                pApp->mousePressed = true;
            break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                pApp->mousePressed = false;
            break;
        }
    }
}

int quitApp(App* pApp) {
    SDL_HideWindow(pApp->pWindow);

    return 0;
}

void renderApp(App* pApp, void (*render)()) {

    if (render) {
        render();
    }
}


int updateApp(App* pApp, void (*update)(),void (*render)()) {
    processAppEvent(pApp);

    if (update) {
        update();
    }
    if (render) {
        renderApp(pApp, render);
    }

    renderApp(pApp,NULL);
    return 0;
}   

void runApp(App* pApp, void (*start)(), void (*update)(), void (*render)()) {
    
    SDL_ShowWindow(pApp->pWindow);
    
    if(initApp(pApp)) {
        return;
    } 

    
    pApp->running = true;
    if (start) {
        start();
    }
    while (pApp->running) {
        updateApp(pApp, update, render);
    }
}
