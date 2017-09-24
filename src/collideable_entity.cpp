#include "collideable_entity.h"

#include <cmath>

using namespace space_invaders;

CollideableEntity::CollideableEntity(Game& game)
  : Entity(game),
    mExtentX(0),
    mExtentY(0),
    mCenterX(0),
    mCenterY(0),
    mEnabled(true)
{
  // ...
}

CollideableEntity::~CollideableEntity()
{
  // ...
}

void CollideableEntity::setWidth(int width)
{
  Entity::setWidth(width);
  mExtentX = (width / 2);
  mCenterX = this->getX() + mExtentX;
}

void CollideableEntity::setHeight(int height)
{
  Entity::setHeight(height);
  mExtentY = (height / 2);
  mCenterY = this->getY() + mExtentY;
}

void CollideableEntity::setExtentX(int extentX)
{
  mExtentX = extentX;
  mCenterX = this->getX() + mExtentX;
  Entity::setWidth(extentX * 2);
}

void CollideableEntity::setExtentY(int extentY)
{
  mExtentY = extentY;
  mCenterY = this->getY() + mExtentY;
  Entity::setHeight(extentY * 2);
}

void CollideableEntity::setCenterX(int centerX)
{
  mCenterX = centerX;
  Entity::setX(mCenterX - mExtentX);
}

void CollideableEntity::setCenterY(int centerY)
{
  mCenterY = centerY;
  Entity::setY(mCenterY - mExtentY);
}

void CollideableEntity::setX(int x)
{
  Entity::setX(x);
  mCenterX = this->getX() + mExtentX;
}

void CollideableEntity::setY(int y)
{
  Entity::setY(y);
  mCenterY = this->getY() + mExtentY;
}

bool CollideableEntity::collides(CollideableEntity& entity) const
{
  // no collision if either entity is currently not enabled.
  if (!this->isEnabled() || !entity.isEnabled()) return false;

  // check whether we have a collisions between the two AABBs.
  auto x = std::abs(mCenterX - entity.mCenterX) < (mExtentX + entity.mExtentX);
  auto y = std::abs(mCenterY - entity.mCenterY) < (mExtentY + entity.mExtentY);
  return x && y;
}

bool CollideableEntity::contains(int x, int y) const
{
  return !(x < (mCenterX - mExtentX))
    || x > (mCenterX + mExtentX)
    || y < (mCenterY - mExtentY)
    || y >(mCenterY + mExtentY);
}