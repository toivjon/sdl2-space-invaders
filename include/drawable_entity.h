/*! An entity abstraction for all entities that are drawable (i.e. renderable).
 *
 * This class encapsulates the required definitions for an entity to enable it
 * to be drawn (i.e. rendered) on the screen. Our Space Invaders implementation
 * uses sprites to draw objects on the screen, which also makes this class to
 * present and handle sprite definitions whenever a draw command is issued.
 */
#ifndef SPACE_INVADERS_DRAWABLE_ENTTIY_H
#define SPACE_INVADERS_DRAWABLE_ENTTIY_H

#include "collideable_entity.h"

// forward declarations in the global namespace.
struct SDL_Renderer;

namespace space_invaders
{
  class DrawableEntity : public CollideableEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    DrawableEntity() = delete;
    DrawableEntity(const DrawableEntity&) = delete;
    DrawableEntity(DrawableEntity&&) = delete;
    DrawableEntity& operator=(const DrawableEntity&) = delete;
    DrawableEntity& operator=(DrawableEntity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    DrawableEntity(Game& game);
    virtual ~DrawableEntity();

    void render(SDL_Renderer& renderer);

    bool isVisible() const { return mVisible; }

    void setVisible(bool visible) { mVisible = visible; }
  private:
    bool mVisible;
  };
}

#endif