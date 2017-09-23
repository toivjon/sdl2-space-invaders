/*! An entity abstraction for all game objects within the Space Invaders game.
 *
 * This class acts as the root of all entities within the game scene. It does
 * contain all the shared definitions that must be present within all entities
 * that are created into the game scene. This also includes the root game and
 * scene instances as well as the 2d-coordinates of the entity.
 */
#ifndef SPACE_INVADERS_ENTITY_H
#define SPACE_INVADERS_ENTITY_H

namespace space_invaders
{
  class Game;
  class Entity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    Entity() = delete;
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    Entity(Game& game) : mGame(game), mX(0), mY(0) {}
    virtual ~Entity() = default;

    int getX() const { return mX; }
    int getY() const { return mY; }

    void setX(x) { mX = x; }
    void setY(y) { mY = y; }
  private:
    Game& mGame;
    int   mX;
    int   mY;
  };
}

#endif