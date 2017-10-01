#ifndef SPACE_INVADERS_PLAY_PLAYER_STATE_H
#define SPACE_INVADERS_PLAY_PLAYER_STATE_H

#include "state.h"

namespace space_invaders
{
  class PlayPlayerState : public State
  {
  public:
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
  };
}

#endif