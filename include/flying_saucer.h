/*! An abstraction for the Space Invaders flying saucer.
 *
 * This structure contains all necessary definitions and functionality for the
 * eventually appearing flying saucer that flies across the top of scene. This
 * special entity can be destroyed by the player to earn bonus points based on
 * the player shot count.
 */
#ifndef SPACE_INVADERS_FLYING_SAUCER_H
#define SPACE_INVADERS_FLYING_SAUCER_H

#include "animated_entity.h"

#include <array>

namespace space_invaders
{
  class FlyingSaucer : public AnimatedEntity
  {
  public:
    /** A constant time interval between appending the flying saucer. */
    static const auto APPEAR_INTERVAL = 1200;
    /** A score table used along with player shot count to resolve points. */
    static const std::array<int, 15> POINT_TABLE;

    // ===============================
    // = forbidden default functions =
    // ===============================

    FlyingSaucer() = delete;
    FlyingSaucer(const FlyingSaucer&) = delete;
    FlyingSaucer(FlyingSaucer&&) = delete;
    FlyingSaucer& operator=(const FlyingSaucer&) = delete;
    FlyingSaucer& operator=(FlyingSaucer&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    FlyingSaucer(Game& game);
    ~FlyingSaucer() override = default;

    void update(unsigned long dt) override;

    void explode();
    void launch();

    int getPoints() const;

    int getAppearingCounter() const { return mAppearingCounter; }
  private:
    int mAppearingCounter;
  };
}

#endif