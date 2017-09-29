/*! An entity abstraction for all entities that present a drawable text.
 *
 * This class presents a textual entity within the game scene. It does really
 * and encapsulation of the 2d drawing context textual presentation functions.
 * It is considered as disabled (i.e. non-collideable) and visible by default.
 */
#ifndef SPACE_INVADERS_TEXT_ENTITY_H
#define SPACE_INVADERS_TEXT_ENTITY_H

#include "drawable_entity.h"

namespace space_invaders
{
  class TextEntity : public DrawableEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    TextEntity() = delete;
    TextEntity(const TextEntity&) = delete;
    TextEntity(TextEntity&&) = delete;
    TextEntity& operator=(const TextEntity&) = delete;
    TextEntity& operator=(TextEntity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    TextEntity(Game& game);
    virtual ~TextEntity();

    void setText(const std::string& text);
    void setColor(const SDL_Color& color);

    const std::string& getText()  const { return mText;   }
    const SDL_Color&   getColor() const { return mColor;  }
  private:
    std::string mText;
    SDL_Color   mColor;
  };
}

#endif