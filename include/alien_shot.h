/*! An abstraction for all alien shots.
 *
 * This structure contains the additional definitions and methods for the alien
 * shots. There are three different alien shots available; rolling, plumbing
 * and the squiggly shot. Each shot has a bit different behavior, which are
 * described in the following table.
 *
 * Rolling shot
 * A "homing" shot that is always launched from the players nearest alien.
 *
 * Plunger shot
 * A shot that follows a predefined alien columns list and is not used when there
 * is only one alien left.
 *
 * Squiggly shot
 * A shot that follows a predefined alien columns list and is not used when the
 * flying saucer is being shown.
 *
 * Table is based on foundings from the following URL:
 * http://www.computerarcheology.com/Arcade/SpaceInvaders/Code.html
 *
 */
#ifndef SPACE_INVADER_ALIEN_SHOT_H
#define SPACE_INVADER_ALIEN_SHOT_H

#include "animated_entity.h"

namespace space_invaders
{
  class AlienShot : public AnimatedEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    AlienShot() = delete;
    AlienShot(const AlienShot&) = delete;
    AlienShot(AlienShot&&) = delete;
    AlienShot& operator=(const AlienShot&) = delete;
    AlienShot& operator=(AlienShot&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    AlienShot(Game& game);
    ~AlienShot() override = default;

    void update(unsigned long dt) override;

    virtual void fire();
    void explode();
    bool isReadyToBeFired(const AlienShot& shot1, const AlienShot& shot2) const;

    int getReloadRate() const;
  private:
    int mProgressTicks;
  };
}


#endif