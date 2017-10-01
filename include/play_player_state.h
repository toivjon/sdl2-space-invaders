/*! A starting state to indicate that the player should prepare to play.
 *
 * This scene creates a simple "PLAY PLAYER<?>" text for the next player that
 * should prepare itself to play the game. This is a typical transition between
 * the players when the multiplayer game mode is being used.
*/
#ifndef SPACE_INVADERS_PLAY_PLAYER_STATE_H
#define SPACE_INVADERS_PLAY_PLAYER_STATE_H

#include "state.h"

namespace space_invaders
{
  class PlayPlayerState : public State
  {
  public:
    /** A definition of ticks before this state automatically proceeds. */
    const int VISIBLITY_TICKS = (30 * 5);

    // ===============================
    // = forbidden default functions =
    // ===============================

    PlayPlayerState() = delete;
    PlayPlayerState(const PlayPlayerState&) = delete;
    PlayPlayerState(PlayPlayerState&&) = delete;
    PlayPlayerState& operator=(const PlayPlayerState&) = delete;
    PlayPlayerState& operator=(PlayPlayerState&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    PlayPlayerState(Game& game);
    virtual ~PlayPlayerState() override = default;

    void update(unsigned long dt);
    void render(SDL_Renderer& renderer);

    void onEnter();
    void onExit();

    void onKeyUp(SDL_KeyboardEvent& event);
    void onKeyDown(SDL_KeyboardEvent& event);
  private:
    int mTickCounter;
  };
}

#endif