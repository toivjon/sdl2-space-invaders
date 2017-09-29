#include "text_entity.h"
#include "game.h"
#include "image.h"

using namespace space_invaders;

TextEntity::TextEntity(Game& game) : DrawableEntity(game), mText(""), mColor({255, 255, 255, 255})
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