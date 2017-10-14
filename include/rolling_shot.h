/*! An abstraction for the rolling alien missile.
*
* This structure contains all necessary definitions required for the handling
* of the alien rolling missile. This missile does follow the next rules:
*
* 1. Missile can be used when the missile lock time has elapsed.
* 2. Missile can be used when the player avatar is enabled.
* 3. Missile can be used when the reload time has been elapsed.
*/
#ifndef SPACE_INVADERS_ROLLING_SHOT_H
#define SPACE_INVADERS_ROLLING_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class RollingShot final : public AlienShot
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    RollingShot() = delete;
    RollingShot(const RollingShot&) = delete;
    RollingShot(RollingShot&&) = delete;
    RollingShot& operator=(const RollingShot&) = delete;
    RollingShot& operator=(RollingShot&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    RollingShot(Game& game, IngameState& state);
    ~RollingShot() override = default;

    void update(unsigned long dt) override;
    void fire() override;

    int getLock() const { return mLock; }
  private:
    int mLock;
  };
}
#endif