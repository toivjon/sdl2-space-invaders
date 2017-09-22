#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

// forward declarations in the global namespace.
struct SDL_Window;
struct SDL_Renderer;

namespace space_invaders
{
  class Game final
  {
  public:
    enum class State { NOT_INITED, INITED, RUNNING, STOPPED };
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
  private:
    State         mState;
    SDL_Window*   mWindow;
    SDL_Renderer* mRenderer;
  };
}

#endif