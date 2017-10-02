/*! An abstraction for the avatar laser beam.
 *
 * This structure contains the required functionality for the laser beam
 * that can be shot by the player avatar. In our implementation, we only
 * use a single shot instance which can be reused during the gameplay.
 */
#ifndef SPACE_INVADERS_AVATAR_LASER_H
#define SPACE_INVADERS_AVATAR_LASER_H

#include "animated_entity.h"

namespace space_invaders
{
  class AvatarLaser : public AnimatedEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    AvatarLaser() = delete;
    AvatarLaser(const AvatarLaser&) = delete;
    AvatarLaser(AvatarLaser&&) = delete;
    AvatarLaser& operator=(const AvatarLaser&) = delete;
    AvatarLaser& operator=(AvatarLaser&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    AvatarLaser(Game& game);
    ~AvatarLaser() override = default;

    void explode();
  };
}

#endif