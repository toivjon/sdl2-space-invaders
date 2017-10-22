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
#include "image.h"

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

    void update(unsigned long dt) override;
    void render(SDL_Renderer& renderer);

    void setImage(ImagePtr image);

    void setClip(const SDL_Rect& clip);
    void setDisappearCountdown(int timer);

    bool isVisible() const { return mVisible; }

    SDL_Rect normalize(const SDL_Rect& rect) const;

          ImagePtr getImage()       { return mImage; }
    const ImagePtr getImage() const { return mImage; }

          SDL_Rect& getClip()       { return mClip; }
    const SDL_Rect& getClip() const { return mClip; }

    void setVisible(bool visible) { mVisible = visible; }
  private:
    bool     mVisible;
    ImagePtr mImage;
    SDL_Rect mClip;
    int      mDisappearCountdown;
  };
}

#endif