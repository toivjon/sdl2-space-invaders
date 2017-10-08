#include "ingame_state.h"
#include "game.h"
#include "player_context.h"

using namespace space_invaders;

IngameState::IngameState(Game& game)
  : State(game),
    mFooterLine(game),
    mAvatar(game),
    mLeftOobDetector(game),
    mRightOobDetector(game),
    mTopOobDetector(game),
    mAvatarLaser(game),
    mLifesText(game),
    mLifeSprite1(game),
    mLifeSprite2(game)
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

  // initialize the out-of-bounds detector for the top side of the scene.
  mTopOobDetector.setX(0);
  mTopOobDetector.setY(0);
  mTopOobDetector.setExtentX(768 / 2);
  mTopOobDetector.setExtentY(70);

  // initialize the text indicating the amount of lifes.
  auto& ctx = mGame.getActivePlayerContext();
  mLifesText.setText(std::to_string(ctx.getLives()));
  mLifesText.setX(27);
  mLifesText.setY(743 - mLifesText.getHeight() + 5);

  // initialize a sprite describing whether the player has at least one life left.
  mLifeSprite1.setImage(mGame.getSpriteSheet());
  mLifeSprite1.setWidth(40);
  mLifeSprite1.setHeight(24);
  mLifeSprite1.setX(66);
  mLifeSprite1.setY(720);
  mLifeSprite1.setClip({ 85, 5, 40, 24 });
  mLifeSprite1.setVisible(ctx.getLives() > 1);

  // initialize a sprite describing whether the player has at least two lifes left.
  mLifeSprite2.setImage(mGame.getSpriteSheet());
  mLifeSprite2.setWidth(40);
  mLifeSprite2.setHeight(24);
  mLifeSprite2.setX(66 + 49);
  mLifeSprite2.setY(720);
  mLifeSprite2.setClip({ 85, 5, 40, 24 });
  mLifeSprite2.setVisible(ctx.getLives() > 2);

  // get aliens from the user context or create them if not yet created.
  mAliens = ctx.getAliens();
  if (mAliens.empty()) {
    for (auto i = 0; i < 55; i++) {
      mAliens.push_back(std::make_shared<Alien>(game, i));
    }
  }
}

void IngameState::update(unsigned long dt)
{
  mFooterLine.update(dt);
  mAvatar.update(dt);
  mAvatarLaser.update(dt);
  for (auto& alien : mAliens) {
    alien->update(dt);
  }

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

  // check whether the avatar laser beam hits something.
  if (mAvatarLaser.isEnabled()) {
    if (mAvatarLaser.collides(mTopOobDetector)) {
      mAvatarLaser.setCurrentAnimation("top-wall-hit");
      mAvatarLaser.explode();
    } else {
      for (auto& alien : mAliens) {
        if (mAvatarLaser.collides(*alien)) {
          // create an alien laser to explode at the alien position.
          mAvatarLaser.setCurrentAnimation("alien-hit");
          mAvatarLaser.explode();
          mAvatarLaser.setX(alien->getCenterX() - mAvatarLaser.getExtentX());
          mAvatarLaser.setY(alien->getCenterY() - mAvatarLaser.getExtentY());
          alien->disappear();

          // add the alien row specific amount of points to the player.
          auto& ctx = mGame.getActivePlayerContext();
          auto points = alien->getPoints();
          ctx.addScore(points);

          // TODO speed up the movement of the aliens.

          break;
        }
      }
    }
  }
}

void IngameState::render(SDL_Renderer& renderer)
{
  mFooterLine.render(renderer);
  mAvatar.render(renderer);
  mAvatarLaser.render(renderer);
  mLifesText.render(renderer);
  mLifeSprite1.render(renderer);
  mLifeSprite2.render(renderer);
  for (auto& alien : mAliens) {
    alien->render(renderer);
  }
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

      // increment the shot count that is used in variety of places.
      auto& ctx = mGame.getActivePlayerContext();
      ctx.setShotCount(ctx.getShotCount() + 1);
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