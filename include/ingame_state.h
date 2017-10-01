/*! The ingame state for the Space Invaders game.
 *
 * This is the state where the player(s) actually play the game. Here we allow
 * users to move and fire with the turret so they can prevent the earch from
 * being invaded by the invaders coming from the space.
 */
#ifndef SPACE_INVADERS_INGAME_STATE_H
#define SPACE_INVADERS_INGAME_STATE_H

#include "state.h"

namespace space_invaders
{
  class IngameState : public State
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    IngameState() = delete;
    IngameState(const IngameState&) = delete;
    IngameState(IngameState&&) = delete;
    IngameState& operator=(const IngameState&) = delete;
    IngameState& operator=(IngameState&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    IngameState(Game& game);
    virtual ~IngameState() override = default;

    void update(unsigned long dt);
    void render(SDL_Renderer& renderer);

    void onEnter();
    void onExit();

    void onKeyUp(SDL_KeyboardEvent& event);
    void onKeyDown(SDL_KeyboardEvent& event);
  };
}

#endif