#include <stdio.h>
#include "sdlApp.h"
#include <math.h>
#include <algorithm>

class Pong {
public:

  struct Circle {
    double x, y, r;
  };

  Pong() : SCREEN_WIDTH(700), SCREEN_HEIGHT(720) {};

  Pong(int width, int height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height) {};

  void run();

  void stop();


private:
  bool isRunning = true;

  const int SCREEN_WIDTH;

  const int SCREEN_HEIGHT;

  SdlApp app;

  void fillCircle(SDL_Surface* screenSurface, Circle c, Uint32 color);
  
  void handlePlayerMovement(SDL_Surface* screenSurface, SDL_Rect& player, float speed, Uint32 dt, bool ptf);

  void handleCollision(Circle& ball, float& ballSpeedX , float& ballSpeedY, SDL_Rect& playerOne, SDL_Rect& playerTwo);

  bool checkCircleInsideWindowX(Circle c);
  bool checkCircleInsideWindowY(Circle c);
  bool checkCircleRectCollision(Circle circle, SDL_Rect rect);
};
