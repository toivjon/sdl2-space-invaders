#include "collideable_entity.h"

#include <algorithm>
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

bool CollideableEntity::collides(const CollideableEntity& entity) const
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

SDL_Rect CollideableEntity::intersection(const CollideableEntity& entity) const
{
  // get a reference to the bounds of both entities.
  const auto& bounds1 = getRect();
  const auto& bounds2 = entity.getRect();

  // define the bounds of the intersection.
  auto x1 = std::max(bounds1.x, bounds2.x);
  auto y1 = std::max(bounds1.y, bounds2.y);
  auto x2 = std::min(bounds1.x + bounds1.w, bounds2.x + bounds2.w);
  auto y2 = std::min(bounds1.y + bounds1.h, bounds2.y + bounds2.h);

  // calculate the dimensions of the intersection bounds.
  auto width = (x2 - x1);
  auto height = (y2 - y1);

  // return the intersection bounds or empty bounds if there is no intersection.
  if (width > 0 && height > 0) {
    return { x1, y1, width, height };
  } else {
    return { 0, 0, 0, 0 };
  }
}