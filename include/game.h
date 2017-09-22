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

          SDL_Window* getWindow()       { return mWindow; }
    const SDL_Window* getWindow() const { return mWindow; }

          SDL_Renderer* getRenderer()       { return mRenderer; }
    const SDL_Renderer* getRenderer() const { return mRenderer; }
  private:
    State         mState;
    SDL_Window*   mWindow;
    SDL_Renderer* mRenderer;
  };
}

#endif