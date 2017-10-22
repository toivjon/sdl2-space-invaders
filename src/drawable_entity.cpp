#include "drawable_entity.h"

#include <algorithm>
#include <SDL.h>

using namespace space_invaders;

DrawableEntity::DrawableEntity(Game& game) 
  : CollideableEntity(game),
    mVisible(true),
    mImage(nullptr),
    mClip({ 0,0,0,0 }),
    mDisappearCountdown(0)
{
  // ...
}

DrawableEntity::~DrawableEntity()
{
  // ...
}

void DrawableEntity::update(unsigned long dt)
{
  if (mDisappearCountdown > 0) {
    mDisappearCountdown--;
    if (mDisappearCountdown <= 0) {
      this->setEnabled(false);
      this->setVisible(false);
    }
  }
  CollideableEntity::update(dt);
}

void DrawableEntity::render(SDL_Renderer& renderer)
{
  if (mVisible && mImage) {
    SDL_RenderCopy(&renderer, mImage->getTexture(), &mClip, &this->getRect());
  }
}

void DrawableEntity::setImage(ImagePtr image)
{
  if (image != nullptr) {
    mClip.x = 0;
    mClip.y = 0;
    mClip.w = image->getWidth();
    mClip.h = image->getHeight();
    setWidth(image->getWidth());
    setHeight(image->getHeight());
  } else {
    mVisible = false;
  }
  mImage = image;
}

void DrawableEntity::setClip(const SDL_Rect& clip)
{
  mClip = clip;
  setWidth(mClip.w);
  setHeight(mClip.h);
}

void DrawableEntity::setDisappearCountdown(int timer)
{
  mDisappearCountdown = std::max(0, timer);
}

SDL_Rect DrawableEntity::normalize(const SDL_Rect& rect) const
{
  SDL_Rect normalizedRect;
  normalizedRect.x = rect.x - getX() + mClip.x;
  normalizedRect.y = rect.y - getY() + mClip.y;
  normalizedRect.w = rect.w;
  normalizedRect.h = rect.h;
  return normalizedRect;
}