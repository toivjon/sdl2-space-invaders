/*! An entity abstraction for all game objects within the Space Invaders game.
 *
 * This class acts as the root of all entities within the game scene. It does
 * contain all the shared definitions that must be present within all entities
 * that are created into the game scene. This also includes the root game and
 * scene instances as well as the 2d-coordinates of the entity.
 */
#ifndef SPACE_INVADERS_ENTITY_H
#define SPACE_INVADERS_ENTITY_H

#include <SDL.h>

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

    Entity(Game& game) : mGame(game), mRect({0,0,0,0}) {}
    virtual ~Entity() = default;

    virtual void update(unsigned long dt) {}

    int getX()      const { return mRect.x; }
    int getY()      const { return mRect.y; }
    int getWidth()  const { return mRect.w; }
    int getHeight() const { return mRect.h; }

    const SDL_Rect& getRect() const { return mRect; }

    virtual void setX(int x)      { mRect.x = x; }
    virtual void setY(int y)      { mRect.y = y; }
    virtual void setWidth(int w)  { mRect.w = w; }
    virtual void setHeight(int h) { mRect.h = h; }
  protected:
    Game&    mGame;
  private:
    SDL_Rect mRect;
  };
}

#endif