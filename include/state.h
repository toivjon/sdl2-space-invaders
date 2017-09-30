/*! An abstraction for all available game states within the Space Invaders.
 *
 * Our implementation of the Space Invaders contains three different scenes,
 * where one state is reserved for the welcoming (i.e. description) states,
 * one state is for the player get-ready message and one is for the ingame.
 */
#ifndef SPACE_INVADERS_STATE_H
#define SPACE_INVADERS_STATE_H

#include <memory>

// forward declarations in the global namespace.
struct SDL_Renderer;
struct SDL_KeyboardEvent;

namespace space_invaders
{
  class Game;
  class State
  {
  public:
    State(Game& game) : mGame(game) {}
    virtual ~State() = 0;

    virtual void update(unsigned long dt) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void onKeyUp(SDL_KeyboardEvent& event) = 0;
    virtual void onKeyDown(SDL_KeyboardEvent& event) = 0;
  protected:
    Game& mGame;
  };
  typedef std::shared_ptr<State> StatePtr;
}

#endif