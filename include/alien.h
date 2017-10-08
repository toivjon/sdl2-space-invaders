/*! An absraction for all space invaders aliens.
 *
 * This structure contains all necessary functionality for each alien entity.
 * There are 55 aliens within the game, which are divided into three different
 * alien types. Each alien type also gives the player a different amount of
 * points when being destroyed by the player.
 */
#ifndef SPACE_INVADERS_ALIEN_H
#define SPACE_INVADERS_ALIEN_H

#include "animated_entity.h"

namespace space_invaders
{
  class Alien : public AnimatedEntity
  {
  public:
    /** The initial step size of the aliens. */
    const int INITIAL_STEP_SIZE = 55;
    /** The amount of aliens per row. */
    const int ALIENS_PER_ROW = 11;

    // ===============================
    // = forbidden default functions =
    // ===============================

    Alien() = delete;
    Alien(const Alien&) = delete;
    Alien(Alien&&) = delete;
    Alien& operator=(const Alien&) = delete;
    Alien& operator=(Alien&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    Alien(Game& game, int index);
    ~Alien() override = default;

    void disappear();

    int getPoints() const { return mPoints; }
  private:
    int resolveYPosition();
  private:
    int mIndex;
    int mPoints;
  };
  typedef std::shared_ptr<Alien> AlienPtr;
}

#endif