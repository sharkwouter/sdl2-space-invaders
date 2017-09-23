#include "game.h"

#include <chrono>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace space_invaders;

inline unsigned long currentMillis()
{
  using namespace std::chrono;
  return (unsigned long)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Game::Game(int width, int height) : mState(State::NOT_INITED), mRenderer(nullptr), mWindow(nullptr), mFont(nullptr), mPreviousTick(0), mDeltaAccumulator(0)
{
  // initialize all SDL2 framework systems.
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }

  // initialize image system for image management.
  if (IMG_Init(IMG_INIT_PNG) == -1) {
    std::cerr << "Unable to initialize IMG: " << IMG_GetError() << std::endl;
    return;
  }

  // initialize TTF system for text rendering.
  if (TTF_Init() == -1) {
    std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
    return;
  }

  // create the main window for the application.
  mWindow = SDL_CreateWindow("SDL2 - Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  if (mWindow == nullptr) {
    std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }

  // create the renderer for the main window.
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mRenderer == nullptr) {
    std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
    return;
  }

  // initialize a font for the application.
  mFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
  if (mFont == nullptr) {
    std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
    return;
  }

  // define the game as ready-to-go!
  mState = State::INITED;
}

Game::~Game()
{
  TTF_CloseFont(mFont);
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int Game::run()
{
  // return with an error code if we do not have a good game state.
  if (mState != State::INITED && mState != State::STOPPED) {
    std::cerr << "Uanble to run the game as the game state is " << (int)mState << std::endl;
    return -1;
  }

  SDL_Event event;
  mState = State::RUNNING;
  mPreviousTick = currentMillis();
  while (mState == State::RUNNING) {
    // poll and handle events from the SDL.
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        mState = State::STOPPED;
        break;
      }
    }

    // calculate the delta between the current and previous tick millis.
    auto millis = currentMillis();
    auto dt = (millis - mPreviousTick);
    mPreviousTick = millis;

    // update game logics with a fixed framerate.
    mDeltaAccumulator += dt;
    static const auto FPS = (1000l / 60l);
    if (mDeltaAccumulator >= FPS) {
      // ... TODO update the logic of the scene objects.
      mDeltaAccumulator -= FPS;
    }

    // clear the rendering context with the black color.
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    // ... TODO render the scene contents into the back buffer

    // present the rendered buffer.
    SDL_RenderPresent(mRenderer);
  }

  return 0;
}