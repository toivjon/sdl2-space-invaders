#include "drawable_entity.h"

using namespace space_invaders;

DrawableEntity::DrawableEntity(Game& game) : CollideableEntity(game), mVisible(true)
{
  // ...
}

DrawableEntity::~DrawableEntity()
{
  // ...
}

void DrawableEntity::render(SDL_Renderer& renderer)
{
  if (mVisible) {
    // ... TODO draw something here?
  }
}