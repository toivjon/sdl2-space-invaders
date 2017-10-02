#include "ingame_state.h"
#include "game.h"

using namespace space_invaders;

IngameState::IngameState(Game& game)
  : State(game),
    mFooterLine(game),
    mAvatar(game),
    mLeftOobDetector(game),
    mRightOobDetector(game),
    mAvatarLaser(game)
{
  // initialoize the green static footer line at the bottom of the screen.
  mFooterLine.setImage(game.getSpriteSheet());
  mFooterLine.setX(0);
  mFooterLine.setY(717);
  mFooterLine.setClip({0, 117, 672, 3});

  // initialize the out-of-bounds detector for the left side of the scene.
  mLeftOobDetector.setX(-100);
  mLeftOobDetector.setY(0);
  mLeftOobDetector.setExtentX(50);
  mLeftOobDetector.setExtentY(768 / 2);

  // initialize the out-of-bounds detector for the right side of the scene.
  mRightOobDetector.setX(672);
  mRightOobDetector.setY(0);
  mRightOobDetector.setExtentX(50);
  mRightOobDetector.setExtentY(768 / 2);
}

void IngameState::update(unsigned long dt)
{
  mFooterLine.update(dt);
  mAvatar.update(dt);
  mAvatarLaser.update(dt);

  // check that the avatar cannot go out-of-bounds from the scene boundaries.
  const auto avatarDirection = mAvatar.getDirectionX();
  if (avatarDirection < 0.f) {
    if (mLeftOobDetector.collides(mAvatar)) {
      mAvatar.setDirectionX(0.f);
      mAvatar.setX(mLeftOobDetector.getX() + mLeftOobDetector.getWidth());
    }
  } else if (avatarDirection > 0.f) {
    if (mRightOobDetector.collides(mAvatar)) {
      mAvatar.setDirectionX(0.f);
      mAvatar.setX(mRightOobDetector.getX() - mAvatar.getWidth());
    }
  }
}

void IngameState::render(SDL_Renderer& renderer)
{
  mFooterLine.render(renderer);
  mAvatar.render(renderer);
  mAvatarLaser.render(renderer);
}

void IngameState::onEnter()
{
  // ...
}

void IngameState::onExit()
{
  // ...
}

void IngameState::onKeyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() < 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled() && mAvatar.getDirectionX() > 0.f) {
      mAvatar.setDirectionX(0.f);
    }
    break;
  case SDLK_SPACE:
    if (mAvatar.isEnabled() && mAvatarLaser.isVisible() == false) {
      mAvatarLaser.setVisible(true);
      mAvatarLaser.setEnabled(true);
      mAvatarLaser.setDirectionY(-1.f);
      mAvatarLaser.setX(mAvatar.getCenterX() - mAvatarLaser.getExtentX());
      mAvatarLaser.setY(mAvatar.getY());
      mAvatarLaser.setCurrentAnimation("normal");
      mAvatarLaser.setAnimationFrame(0);

      // TODO maintain the laser counter... in user context?
    }
    break;
  }
}

void IngameState::onKeyDown(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_LEFT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(-1.f);
    }
    break;
  case SDLK_RIGHT:
    if (mAvatar.isEnabled()) {
      mAvatar.setDirectionX(1.f);
    }
    break;
  }
}