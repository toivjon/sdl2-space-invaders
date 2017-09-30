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
    /** A constant amount of toggles to perform after #blink is called. */
    const int DEFAULT_BLINK_COUNT = 30;
    /** A constant amount of updates (i.e. interval) between the blinks. */
    const int DEFAULT_BLINK_FREQUENCY = 5;

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

    void update(unsigned long dt) override;

    void setText(const std::string& text);
    void setColor(const SDL_Color& color);

    void blink();

    void setBlinkCount(int count)         { mBlinkCount = count;          }
    void setBlinkFrequency(int frequency) { mBlinkFrequency = frequency;  }

    const std::string& getText()  const { return mText;   }
    const SDL_Color&   getColor() const { return mColor;  }
  private:
    std::string mText;
    SDL_Color   mColor;
    int         mBlinks;
    int         mBlinkTimer;
    int         mBlinkCount;
    int         mBlinkFrequency;
  };
}

#endif