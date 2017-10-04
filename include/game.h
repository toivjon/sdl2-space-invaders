/*! A simple implementation of the legendary Space Invaders game for the SDL2.
 *
 * This game is a SDL2 version of the legendary Space Invaders game, which was
 * released in 1978 by Taito Corporation. This version uses 2D drawing context
 * from the SDL2 framework to draw items on the screen. Game also uses three
 * scenes, which also act as the states of the game. Scenes are following:
 *
 * 1. Welcome
 * 2. Player start
 * 3. Ingame
 * 
 * Welcome scene contains the introduction and control descriptions about how
 * to play the game. Player start contains a description that a particular
 * player should get ready as the game is going to start soon, while the ingame
 * scene contains the actual gameplay where aliens try to invade earth.
 */
#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

#include "scene.h"
#include "image.h"
#include "player_context.h"

// forward declarations in the global namespace.
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

namespace space_invaders
{
  class Game final
  {
  public:
    enum class State { NOT_INITED, INITED, RUNNING, STOPPED };
    enum class Player { PLAYER_1, PLAYER_2 };
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    Game() = delete;
    Game(const Game& game) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    Game(int width, int height);
    ~Game();

    int run();

    void setActivePlayer(Player player);

    Player getActivePlayer() const { return mActivePlayer; }
    
    int getPlayerCount() const            { return mPlayerCount;        }
    void setPlayerCount(int playerCount)  { mPlayerCount = playerCount; }

          SDL_Window* getWindow()       { return mWindow; }
    const SDL_Window* getWindow() const { return mWindow; }

          SDL_Renderer* getRenderer()       { return mRenderer; }
    const SDL_Renderer* getRenderer() const { return mRenderer; }

          _TTF_Font* getFont()        { return mFont; }
    const _TTF_Font* getFont() const  { return mFont; }

          ScenePtr getScene()       { return mScene;  }
    const ScenePtr getScene() const { return mScene;  }

          ImagePtr getSpriteSheet()       { return mSpriteSheet; }
    const ImagePtr getSpriteSheet() const { return mSpriteSheet; }

          PlayerContext& getPlayerContext1()        { return mPlayerContext1; }
    const PlayerContext& getPlayerContext1() const  { return mPlayerContext1; }

          PlayerContext& getPlayerContext2()        { return mPlayerContext2; }
    const PlayerContext& getPlayerContext2() const  { return mPlayerContext2; }
  private:
    State         mState;
    SDL_Window*   mWindow;
    SDL_Renderer* mRenderer;
    _TTF_Font*    mFont;
    unsigned long mPreviousTick;
    unsigned long mDeltaAccumulator;
    ScenePtr      mScene;
    ImagePtr      mSpriteSheet;
    int           mPlayerCount;
    Player        mActivePlayer;
    PlayerContext mPlayerContext1;
    PlayerContext mPlayerContext2;
  };
}

#endif