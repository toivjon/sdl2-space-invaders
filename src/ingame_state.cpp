#include "ingame_state.h"
#include "game.h"

using namespace space_invaders;

IngameState::IngameState(Game& game)
  : State(game),
    mFooterLine(game),
    mAvatar(game)
{
  // initialoize the green static footer line at the bottom of the screen.
  mFooterLine.setImage(game.getSpriteSheet());
  mFooterLine.setX(0);
  mFooterLine.setY(717);
  mFooterLine.setClip({0, 117, 672, 3});
}

void IngameState::update(unsigned long dt)
{
  mFooterLine.update(dt);
  mAvatar.update(dt);
}

void IngameState::render(SDL_Renderer& renderer)
{
  mFooterLine.render(renderer);
  mAvatar.render(renderer);
}

void IngameState::onEnter()
{
  // ...
}

void IngameState::onExit()
{
  // ...
}

void IngameState::onKeyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() < 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() > 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  }
}

void IngameState::onKeyDown(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(-1.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(1.f);
    }
    break;
  }
}