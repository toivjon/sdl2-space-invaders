/*! An abstraction of all entities that are movable and have a sprite image.
 *
 * This class encapsulates the all necessary functionality for all entities for
 * collideable, movable and drawable sprite entities. For example the player
 * avatar and all enemies should be derived from this structure.
 */
#ifndef SPACE_INVADERS_MOVABLE_ENTITY_H
#define SPACE_INVADERS_MOVABLE_ENTITY_H

#include "drawable_entity.h"

namespace space_invaders
{
  class MovableEntity : public DrawableEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    MovableEntity() = delete;
    MovableEntity(const MovableEntity&) = delete;
    MovableEntity(MovableEntity&&) = delete;
    MovableEntity& operator=(const MovableEntity&) = delete;
    MovableEntity& operator=(MovableEntity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    MovableEntity(Game& game);
    ~MovableEntity() override = default;

    void update(unsigned long dt) override;

    void setStepSize(int stepSize);

    void setVelocity(float velocity)  { mVelocity = velocity; }
    void setDirectionX(float x)       { mDirectionX = x;      }
    void setDirectionY(float y)       { mDirectionY = y;      }

    int getStepSize() const     { return mStepSize;     }
    int getStepCounter() const  { return mStepCounter;  }
    float getVelocity() const   { return mVelocity;     }
    float getDirectionX() const { return mDirectionX;   }
    float getDirectionY() const { return mDirectionY;   }
  private:
    int   mStepSize;
    int   mStepCounter;
    float mVelocity;
    float mDirectionX;
    float mDirectionY;
  };
}

#endif