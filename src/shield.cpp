#include "shield.h"
#include "game.h"

#include <iostream> // TODO for debugging only

using namespace space_invaders;

Shield::Shield(Game& game) : DrawableEntity(game)
{
  setImage(mGame.getSpriteSheet());
  setClip({ 293, 5, 66, 48 });
}

bool Shield::collides(CollideableEntity& entity) const
{
  if (CollideableEntity::collides(entity)) {
    // TODO perform a pixel wise collision!?
    std::cout << "collides with shield" << std::endl;
    return true;
  }
  return false;
}