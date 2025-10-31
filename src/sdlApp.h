#include <stdio.h>
#include <SDL.h>



class SdlApp {
public:
  //default constructor
  SdlApp() = default;


  bool init(int width, int height);

  bool render();

  void close();

  SDL_Window* getWindow() {
    return window;
  }



private:
  SDL_Window* window = NULL;

  SDL_Surface* screenSurface = NULL;

};

