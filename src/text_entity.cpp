#include "text_entity.h"
#include "game.h"
#include "image.h"

using namespace space_invaders;

TextEntity::TextEntity(Game& game) : DrawableEntity(game),
  mText(""), 
  mColor({255, 255, 255, 255}),
  mBlinks(0),
  mBlinkTimer(0),
  mBlinkCount(DEFAULT_BLINK_COUNT),
  mBlinkFrequency(DEFAULT_BLINK_FREQUENCY)

{
  this->setEnabled(false);
}

TextEntity::~TextEntity()
{
  // ...
}

void TextEntity::setText(const std::string& text)
{
  if (mText != text) {
    mText = text;
    setImage(Image::fromText(mGame.getRenderer(), mText, mColor, mGame.getFont()));
  }
}

void TextEntity::setColor(const SDL_Color& color)
{
  if (color.r != mColor.r || color.g != mColor.g || color.b != mColor.b || color.a != mColor.a) {
    mColor = color;
    setImage(Image::fromText(mGame.getRenderer(), mText, mColor, mGame.getFont()));
  }
}

void TextEntity::update(unsigned long dt)
{
  DrawableEntity::update(dt);
  if (mBlinks > 0 || mBlinks == -1) {
    mBlinkTimer--;
    if (mBlinkTimer == 0) {
      this->setVisible(!this->isVisible());
      mBlinks--;
      mBlinks = (mBlinks > -1 ? mBlinks : -1);
      if (mBlinks > 0 || mBlinks == -1) {
        mBlinkTimer = mBlinkFrequency;
      }
    }
  }
}

void TextEntity::blink()
{
  if (this->isVisible() || mBlinks > 0) {
    this->setVisible(true);
    mBlinks = mBlinkCount;
    mBlinkTimer = mBlinkFrequency;
  }
}