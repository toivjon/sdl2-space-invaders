/*! An abstraction for all player shields.
 *
 * This structure contains the logics required for the player avatar shields.
 * In the original Space Invaders, there are four shields that player mayer use
 * to protect the avatar against the alien laser shots.
 *
 * Shields are destructable, where destructions consume a part of the shield. In
 * fact, there are three different things that must consume shields.
 *
 * 1. Alien shots
 * 2. Player shots
 * 3. Alien contact
 *
 * Each collision with the previously mentioned entity must consume a part of
 * the shield where the collision occurs. Collided shots must be first exploded
 * and then use the explosion sprite to consume part of the shield pixels away.
 * Note that avatar and alien lasers collides with a different explosion sprite.
 *
 */
#ifndef SPACE_INVADERS_SHIELD_H
#define SPACE_INVADERS_SHIELD_H

#include "drawable_entity.h"

#include <memory>

namespace space_invaders
{
  class Shield : public DrawableEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    Shield() = delete;
    Shield(const Shield&) = delete;
    Shield(Shield&&) = delete;
    Shield& operator=(const Shield&) = delete;
    Shield& operator=(Shield&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    Shield(Game& game);
    ~Shield() override = default;

    bool collides(CollideableEntity& entity) const;

    bool hasVisiblePixel(const DrawableEntity& entity, int x, int y) const;
    bool hasVisiblePixel(void* pixels, int pitch, int x, int y) const;
  };
  typedef std::shared_ptr<Shield> ShieldPtr;
}

#endif