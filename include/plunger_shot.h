/*! An abstraction for the plunger alien missile.
 *
 * This structure contains all necessary definitions required for the handling
 * of the alien plunger missile. This missile does follow the next rules:
 *
 * 1. Missile can be used when there is at least two or more aliens left.
 * 2. Missile can be used when the player avatar is enabled.
 * 3. Missile can be used when the reload time has been elapsed.
 */
#ifndef SPACE_INVADERS_PLUNGER_SHOT_H
#define SPACE_INVADERS_PLUNGER_SHOT_H

#include "alien_shot.h"

#include <array>

namespace space_invaders
{
  class IngameState;
  class PlungerShot final : public AlienShot
  {
  public:
    static const std::array<int, 15> SHOT_COLUMNS;

    // ===============================
    // = forbidden default functions =
    // ===============================

    PlungerShot() = delete;
    PlungerShot(const PlungerShot&) = delete;
    PlungerShot(PlungerShot&&) = delete;
    PlungerShot& operator=(const PlungerShot&) = delete;
    PlungerShot& operator=(PlungerShot&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    PlungerShot(Game& game, IngameState& state);
    ~PlungerShot() override = default;

    void fire() override;
  private:
    int mNextShotColumnIndex;
  };
}


#endif