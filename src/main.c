#define SDL_MAIN_USE_CALLBACKS 1 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_DisplayID displayID;
    SDL_Rect displayRect;
    
    if(!(displayID = SDL_GetPrimaryDisplay())) {
        SDL_Log("Failed getting DisplayID");
        return SDL_APP_FAILURE;
    } else if(!SDL_GetDisplayBounds(displayID , &displayRect)) {
        SDL_Log("Failed getting window bounds");
        return SDL_APP_FAILURE;
    } else if (!SDL_CreateWindowAndRenderer("GameWindow", displayRect.w, displayRect.h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    const bool* keylist = SDL_GetKeyboardState(0);

    if (keylist[SDL_SCANCODE_ESCAPE] ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_Log("Quit done");
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}