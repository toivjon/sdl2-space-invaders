#include "game.h"
#include "welcome_scene.h"

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

Game::Game(int width, int height) : mState(State::NOT_INITED),
  mRenderer(nullptr),
  mWindow(nullptr),
  mFont(nullptr),
  mPreviousTick(0),
  mDeltaAccumulator(0),
  mScene(nullptr),
  mSpriteSheet(nullptr)
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

  // load the sprite sheet from the local filesystem.
  mSpriteSheet = Image::fromFile(mRenderer, "spritesheet.png");
  if (mSpriteSheet == nullptr) {
    std::cerr << "Unable to load sprite sheet from local filesystem." << std::endl;
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

  // set the welcoming scene as the initial scene.
  this->setScene(std::make_shared<WelcomeScene>(*this));

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
      mScene->update(FPS);
      mDeltaAccumulator -= FPS;
    }

    // clear the rendering context with the black color.
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    // render the scene on the back buffer.
    mScene->render(*mRenderer);

    // present the rendered buffer.
    SDL_RenderPresent(mRenderer);
  }

  return 0;
}

void Game::setScene(ScenePtr scene)
{
  if (scene) {
    // exit the previous scene (if any).
    if (mScene) {
      mScene->exit();
    }

    // apply and enter the new scene.
    mScene = scene;
    mScene->enter();
  }
}