/*! An entity abstraction for all entities that are collideable.
 * 
 * This class encapsulates the required definitions for an entity to perform a
 * collision check with an another entity. The abstraction uses an axis-aligned
 * bounding box to encapsulate and check whether a collision is executed.
 */
#ifndef SPACE_INVADERS_COLLIDEABLE_ENTITY_H
#define SPACE_INVADERS_COLLIDEABLE_ENTITY_H

#include "entity.h"

namespace space_invaders
{
  class CollideableEntity : public Entity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    CollideableEntity() = delete;
    CollideableEntity(const CollideableEntity&) = delete;
    CollideableEntity(CollideableEntity&&) = delete;
    CollideableEntity& operator=(const CollideableEntity&) = delete;
    CollideableEntity& operator=(CollideableEntity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    CollideableEntity(Game& game);
    virtual ~CollideableEntity();

    void setExtentX(int extentX);
    void setExtentY(int extentY);
    void setCenterX(int centerX);
    void setCenterY(int centerY);

    void setX(int x) override;
    void setY(int y) override;
    void setWidth(int width) override;
    void setHeight(int height) override;

    virtual bool collides(CollideableEntity& entity) const;
    bool contains(int x, int y) const;

    int getExtentX() const { return mExtentX; }
    int getExtentY() const { return mExtentY; }
    int getCenterX() const { return mCenterX; }
    int getCenterY() const { return mCenterY; }
    bool isEnabled() const { return mEnabled; }

    void setEnabled(bool enabled) { mEnabled = enabled; }
  private:
    int  mExtentX;
    int  mExtentY;
    int  mCenterX;
    int  mCenterY;
    bool mEnabled;
  };
}

#endif