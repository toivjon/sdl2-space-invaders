#include "drawable_entity.h"

#include <SDL.h>

using namespace space_invaders;

DrawableEntity::DrawableEntity(Game& game) : CollideableEntity(game), mVisible(true), mImage(nullptr), mClip({ 0,0,0,0 })
{
  // ...
}

DrawableEntity::~DrawableEntity()
{
  // ...
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