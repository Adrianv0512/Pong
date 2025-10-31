#include "pong.h"

void Pong::fillCircle(SDL_Surface* surface, Pong::Circle c, Uint32 color) {
  double rSquared = pow(c.r, 2);
  for (double x = c.x - c.r; x <= c.x + c.r; x++) {
    for (double y = c.y - c.r; y <= c.y + c.r; y++) {
      double dSquared = pow((x - c.x),2) + pow((y - c.y), 2);
      if (dSquared < rSquared) {
        SDL_Rect pixel = {x, y, 1, 1};
        SDL_FillRect(surface, &pixel, color);
      }
    }
  }
}


void Pong::handlePlayerMovement(SDL_Surface* screenSurface, SDL_Rect& player, float speed, Uint32 dt, bool ptf) {

    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
    bool playerTwoFlag = ptf;
    
    if (keyStates[SDL_SCANCODE_S] && !ptf) {
      SDL_FillRect(screenSurface, &player, 0x00000000);
      if (player.y + player.h + (speed * dt) < SCREEN_HEIGHT) player.y += (speed * dt);
    }
    if (keyStates[SDL_SCANCODE_W] && !ptf) {
      SDL_FillRect(screenSurface, &player, 0x00000000);
      if (player.y - (speed * dt) > 0) player.y -= speed * dt;
    }

    if (keyStates[SDL_SCANCODE_DOWN] && ptf) {
      SDL_FillRect(screenSurface, &player, 0x00000000);
      if (player.y + player.h + (speed * dt) < SCREEN_HEIGHT) player.y += speed * dt;
    }
    if (keyStates[SDL_SCANCODE_UP] && ptf) {
      SDL_FillRect(screenSurface, &player, 0x00000000);
      if (player.y - (speed * dt) > 0) player.y -= speed * dt;
    }

}

bool Pong::checkCircleInsideWindowX(Circle c) {
  return c.x - c.r >= 0 && c.x + c.r <= SCREEN_WIDTH;
}
bool Pong::checkCircleInsideWindowY(Circle c) {

  return c.y - c.r >= 0 && c.y + c.r <= SCREEN_HEIGHT;
}
bool Pong::checkCircleRectCollision(Circle circle, SDL_Rect rect) {
  double closestX = std::clamp<double>(circle.x, rect.x, rect.x + rect.w);
  double closestY = std::clamp<double>(circle.y, rect.y, rect.y + rect.h);

  double dx = circle.x - closestX;
  double dy = circle.y - closestY;

  return (dx*dx + dy*dy) <= (circle.r * circle.r);
}

void Pong::handleCollision(Circle& ball , float& ballSpeedX , float& ballSpeedY, SDL_Rect& playerOne, SDL_Rect& playerTwo) {
    float tmp = -0.500;
    if (!checkCircleInsideWindowX(ball)) {
      ball.x = std::clamp(ball.x, 0 + ball.r, SCREEN_WIDTH - ball.r);
      ballSpeedX = -ballSpeedX;
    }
    if (!checkCircleInsideWindowY(ball)) {
      ball.y = std::clamp(ball.y, 0 + ball.r, SCREEN_HEIGHT - ball.r);
      ballSpeedY = -ballSpeedY;
    }
    
    if(checkCircleRectCollision(ball, playerOne)) {
      ball.x = std::clamp(ball.x, playerOne.x + playerOne.w + ball.r, playerOne.x + playerOne.w + ball.r);
      ballSpeedX = -ballSpeedX;
      ballSpeedY = 0.1 * (ball.y - (playerOne.y + playerOne.h / 2));
      ballSpeedY = std::clamp(ballSpeedY, tmp, -tmp);
    }
    if(checkCircleRectCollision(ball, playerTwo)) {
      ball.x = std::clamp(ball.x, playerTwo.x - ball.r - 1, playerTwo.x - ball.r - 1);
      ballSpeedX = -ballSpeedX;
      ballSpeedY = 0.1 * (ball.y - (playerTwo.y + playerTwo.h / 2));
      ballSpeedY = std::clamp(ballSpeedY, tmp, -tmp);
    }
    
    
    
}

void Pong::run() {
  
  app = SdlApp();

  SDL_Event e;
  SDL_Rect playerOne = {100,450,25,100};
  SDL_Rect playerTwo = {600, 450, 25, 100};
  Pong::Circle ball = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10};
  float speed = 1;
  float ballSpeedX = .5;
  float ballSpeedY = 0;
  app.init(SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Surface* screenSurface = SDL_GetWindowSurface(app.getWindow());
  float difficulty = 0.0;

  while (isRunning) {
    
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT:
          isRunning = false;
          break;
      }
    }
    

    static Uint64 startTime = SDL_GetTicks();
    Uint32 now = SDL_GetTicks();
    Uint32 dt = (now - startTime);
    startTime = now;
    
    handlePlayerMovement(screenSurface, playerOne, speed, dt, false);

    handlePlayerMovement(screenSurface, playerTwo, speed, dt, true);

    fillCircle(screenSurface, ball, 0x00000000);

    handleCollision(ball, ballSpeedX, ballSpeedY, playerOne, playerTwo);
    
    ball.x += (ballSpeedX) * dt;
    ball.y += (ballSpeedY) * dt;

    fillCircle(screenSurface, ball, 0xffffffff);
    SDL_FillRect(screenSurface, &playerOne, 0xffffffff);
    SDL_FillRect(screenSurface, &playerTwo, 0xffffffff);

    SDL_UpdateWindowSurface(app.getWindow());

  }
}

void Pong::stop() {
  app.close();
}
