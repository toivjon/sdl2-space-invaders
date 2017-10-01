#include "movable_entity.h"

#include <algorithm>

using namespace space_invaders;

MovableEntity::MovableEntity(Game& game)
  : DrawableEntity(game),
    mStepSize(0),
    mStepCounter(0),
    mVelocity(0.f),
    mDirectionX(0.f),
    mDirectionY(0.f)
{
  // ...
}

void MovableEntity::update(unsigned long dt)
{
  DrawableEntity::update(dt);
  mStepCounter = std::max(0, mStepCounter - 1);
  if (mStepCounter <= 0) {
    this->setX(this->getX() + static_cast<int>(mDirectionX * mVelocity) * dt);
    this->setY(this->getY() + static_cast<int>(mDirectionY * mVelocity) * dt);
    mStepCounter = mStepSize;
  }
}

void MovableEntity::setStepSize(int stepSize)
{
  mStepSize = stepSize;
  mStepCounter = stepSize;
}