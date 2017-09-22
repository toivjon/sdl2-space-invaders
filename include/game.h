#ifndef SPACE_INVADERS_GAME_H
#define SPACE_INVADERS_GAME_H

namespace space_invaders
{
  class Game final
  {
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
  };
}

#endif