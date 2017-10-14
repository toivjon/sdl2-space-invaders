/*! An abstraction for the squiggly alien missile.
*
* This structure contains all necessary definitions required for the handling
* of the alien squiggly missile. This missile does follow the next rules:
*
* 1. Missile can be used when the flying saucer is not visible.
* 2. Missile can be used when the player avatar is enabled.
* 3. Missile can be used when the reload time has been elapsed.
*/
#ifndef SPACE_INVADERS_SQUIGGLY_SHOT_H
#define SPACE_INVADERS_SQUIGGLY_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class IngameState;
  class SquigglyShot final : public AlienShot
  {
  public:
    static const std::array<int, 15> SHOT_COLUMNS;

    // ===============================
    // = forbidden default functions =
    // ===============================

    SquigglyShot() = delete;
    SquigglyShot(const SquigglyShot&) = delete;
    SquigglyShot(SquigglyShot&&) = delete;
    SquigglyShot& operator=(const SquigglyShot&) = delete;
    SquigglyShot& operator=(SquigglyShot&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    SquigglyShot(Game& game, IngameState& state);
    ~SquigglyShot() override = default;

    void fire() override;
  private:
    int mNextShotColumnIndex;
  };
}

#endif