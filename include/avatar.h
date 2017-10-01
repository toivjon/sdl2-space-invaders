/*! An abstraction for the player avatar entity.
 *
 * This structure contains the additional definitions required for the player
 * avatar object, which is the cannon tower that can be moved by the player.
 */
#ifndef SPACE_INVADERS_AVATAR_H
#define SPACE_INVADERS_AVATAR_H

#include "animated_entity.h"

namespace space_invaders
{
  class Avatar : public AnimatedEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    Avatar() = delete;
    Avatar(const Avatar&) = delete;
    Avatar(Avatar&&) = delete;
    Avatar& operator=(const Avatar&) = delete;
    Avatar& operator=(Avatar&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    Avatar(Game& game);
    ~Avatar() override = default;

    void explode();
    void reset();
  };
}

#endif