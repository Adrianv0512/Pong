#include "sdlApp.h"



bool SdlApp::init(int width, int height) {
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  }
  return true;
}

bool SdlApp::render() {

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  } else {
    screenSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(screenSurface, NULL, 0xffffffff);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(10000);
  }

  return true;
}

void SdlApp::close() {

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
