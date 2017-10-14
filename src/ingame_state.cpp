#include "ingame_state.h"
#include "game.h"
#include "player_context.h"
#include "play_player_state.h"

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
    mLifeSprite2(game),
    mAlienLeftDirector(game),
    mAlienRightDirector(game),
    mGameOverText(game),
    mFlyingSaucer(game),
    mPlungerShot(game, *this),
    mSquigglyShot(game, *this),
    mRollingShot(game, *this)
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

  // initialize the left alien director for alien movement direction change.
  mAlienLeftDirector.setX(-45);
  mAlienLeftDirector.setY(0);
  mAlienLeftDirector.setExtentX(45);
  mAlienLeftDirector.setExtentY(768 / 2);

  // initialize the right alien director for alien movement direction change.
  mAlienRightDirector.setX(672 - 45);
  mAlienRightDirector.setY(0);
  mAlienRightDirector.setExtentX(45);
  mAlienRightDirector.setExtentY(768 / 2);

  // initialize the text that indicates that the game has ended.
  mGameOverText.setText("GAME OVER");
  mGameOverText.setColor({245, 3, 5, 255 });
  mGameOverText.setX(672 / 2 - mGameOverText.getExtentX());
  mGameOverText.setY(135);
  mGameOverText.setVisible(false);
}

void IngameState::update(unsigned long dt)
{
  // skip logical updates if the game has ended.
  if (mGameOverText.isVisible()) {
    return;
  }

  mFooterLine.update(dt);
  mAvatar.update(dt);
  mAvatarLaser.update(dt);
  mFlyingSaucer.update(dt);
  mPlungerShot.update(dt);
  mSquigglyShot.update(dt);
  mRollingShot.update(dt);

  // decrement the relaunch timer if it has been activated or handle destruction state.
  auto& ctx = mGame.getActivePlayerContext();
  auto relaunchTimer = ctx.getRelaunchTimer();
  if (relaunchTimer > 0) {
    relaunchTimer--;
    ctx.setRelaunchTimer(relaunchTimer);
    return;
  } else if (mAvatar.isEnabled() == false) {
    const auto playerCount = mGame.getPlayerCount();
    if (playerCount == 1) {
      // ::: SINGLE PLAYER :::
      // check whether it's time to end the game or just reset the avatar.
      if (ctx.getLives() <= 0) {
        // check and update the hi-score if necessary.
        const auto score = ctx.getScore();
        if (mGame.getHiScore() < score) {
          mGame.setHiScore(score);
        }
        mGameOverText.setVisible(true);
        return;
      } else {
        // refresh the amount of lifes indicators.
        const auto lives = ctx.getLives();
        mLifesText.setText(std::to_string(lives));
        if (lives == 2) {
          mLifeSprite2.setVisible(false);
          mLifeSprite1.setVisible(true);
        } else if (lives == 1) {
          mLifeSprite2.setVisible(false);
          mLifeSprite1.setVisible(false);
        }

        // reset the avatar state.
        mAvatar.reset();
      }
    } else {
      // ::: MULTI-PLAYER :::
      // store the current state of the player into the player context.
      ctx.setAliens(mAliens);
      // TODO store shields.

      // perform additional actions based on the currently active player.
      const auto activePlayer = mGame.getActivePlayer();
      if (activePlayer == Game::Player::PLAYER_1) {
        // player one was playing so we can now switch to next player.
        mGame.setActivePlayer(Game::Player::PLAYER_2);
        return;
      } else {
        // player two was playing so we should now check whether to end the game.
        auto& player1Ctx = mGame.getPlayerContext1();
        auto& player2Ctx = mGame.getPlayerContext2();
        if (player2Ctx.getLives() <= 0) {
          // check and update player1 the hi-score if necessary.
          const auto player1Score = player1Ctx.getScore();
          if (mGame.getHiScore() < player1Score) {
            mGame.setHiScore(player1Score);
          }

          // check and update player2 the hi-score if necessary.
          const auto player2Score = player2Ctx.getScore();
          if (mGame.getHiScore() < player2Score) {
            mGame.setHiScore(player2Score);
          }

          // show the game over text and also the score for the 1st player.
          mGameOverText.setVisible(true);
          auto scene = mGame.getScene();
          auto score1 = scene->getScore1Text();
          score1->setVisible(true);
          return;
        } else {
          // was not the last life, so we can just switch to next player.
          mGame.setActivePlayer(Game::Player::PLAYER_1);
          return;
        }
      }
    }
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

  // check whether any of the aliens hits the alien director bounds.
  auto alienMovementChangeRequired = false;
  auto aliensDirection = mAliens[0]->getDirectionX();
  for (auto& alien : mAliens) {
    if (aliensDirection > 0) {
      if (mAlienRightDirector.collides(*alien)) {
        alienMovementChangeRequired = true;
        break;
      }
    } else {
      if (mAlienLeftDirector.collides(*alien)) {
        alienMovementChangeRequired = true;
        break;
      }
    }
  }

  // iterate over aliens and perform alien specific update operations.
  auto activeAlienCount = 0;
  if (mAvatar.isEnabled()) {
    for (auto& alien : mAliens) {
      // drop alien downwards and change the movement if required.
      if (alienMovementChangeRequired) {
        alien->setDirectionX(-aliensDirection);
        alien->setY(alien->getY() + alien->getHeight());
      }

      // perform active calculation and update active aliens.
      if (alien->isVisible()) {
        activeAlienCount++;
        alien->update(dt);

        // check whether the target alien has just landed or hit the player.
        if (alien->collides(mFooterLine)) {
          mAvatar.explode();
        } else if (alien->collides(mAvatar)) {
          mAvatar.explode();
        }
      }
    }
  }

  // check whether all aliens are destroyed i.e. the level is cleared.
  if (activeAlienCount <= 0) {
    ctx.setLevel(ctx.getLevel() + 1);
    auto scene = mGame.getScene();
    scene->setState(std::make_shared<PlayPlayerState>(mGame));
    return;
  }

  // check whether the avatar laser beam hits something.
  if (mAvatarLaser.isEnabled()) {
    if (mAvatarLaser.collides(mTopOobDetector)) {
      mAvatarLaser.setCurrentAnimation("top-wall-hit");
      mAvatarLaser.explode();
    } else if (mAvatarLaser.collides(mFlyingSaucer)) {
      // hide the avatar laser shot.
      mAvatarLaser.setDirectionY(0);
      mAvatarLaser.setEnabled(false);
      mAvatarLaser.setVisible(false);

      // change the flying saucer to perform explosion.
      mFlyingSaucer.explode();

      // add points for the player based on the shot count.
      auto& ctx = mGame.getActivePlayerContext();
      auto points = mFlyingSaucer.getPoints();
      ctx.addScore(points);
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

          // speed up the movement of the aliens.
          auto newStepSize = alien->getStepSize() - Alien::STEP_DECREMENT_SIZE;
          for (auto& a : mAliens) {
            a->setStepSize(newStepSize);
            a->setAnimationStepSize(newStepSize);
          }
          break;
        }
      }
    }
  }

  // create the rolling missile if it's being ready.
  if (mAvatar.isEnabled() && mRollingShot.isReadyToBeFired() && mRollingShot.getLock() <= 0) {
    mRollingShot.fire();
  }

  // create an alien plunger missile if there is more than one alien and if its being reloaded.
  if (mAvatar.isEnabled() && activeAlienCount > 1 && mPlungerShot.isReadyToBeFired()) {
    mPlungerShot.fire();
  }

  // create an alien squiggly missile or the flying saucer if either is currently desired.
  if (mAvatar.isEnabled() && mSquigglyShot.isReadyToBeFired() && !mFlyingSaucer.isVisible()) {
    // check whether it is time to launch the flying saucer.
    if (mFlyingSaucer.getAppearingCounter() <= 0 && activeAlienCount >= 8) {
      mFlyingSaucer.launch();
    } else {
      mSquigglyShot.fire();
    }
  }

  // check whether the rolling shot hits something.
  if (mRollingShot.isVisible()) {
    if (mRollingShot.collides(mAvatar)) {
      // hide the shot and explode the avatar.
      mRollingShot.setEnabled(false);
      mRollingShot.setVisible(false);
      mAvatar.explode();
    } else if (mRollingShot.collides(mFooterLine)) {
      // explode at the footer.
      mRollingShot.explode();
    } else if (mRollingShot.collides(mAvatarLaser)) {
      // explode at the collision.
      mRollingShot.setEnabled(false);
      mRollingShot.setVisible(false);
      mAvatarLaser.explode();
    } else {
      // TODO handle collisions with the shields.
    }
  }

  // check whether the plunger shot hits something.
  if (mPlungerShot.isVisible()) {
    if (mPlungerShot.collides(mAvatar)) {
      // hide the shot and explode the avatar.
      mPlungerShot.setEnabled(false);
      mPlungerShot.setVisible(false);
      mAvatar.explode();
    } else if (mPlungerShot.collides(mFooterLine)) {
      // explode at the footer.
      mPlungerShot.explode();
    } else if (mPlungerShot.collides(mAvatarLaser)) {
      // explode at the collision.
      mPlungerShot.setEnabled(false);
      mPlungerShot.setVisible(false);
      mAvatarLaser.explode();
    } else {
      // TODO handle collisions with the shields.
    }
  }

  // check whether the squiggly shot hits something.
  if (mSquigglyShot.isVisible()) {
    if (mSquigglyShot.collides(mAvatar)) {
      // hide the shot and explode the avatar.
      mSquigglyShot.setEnabled(false);
      mSquigglyShot.setVisible(false);
      mAvatar.explode();
    } else if (mSquigglyShot.collides(mFooterLine)) {
      // explode at the footer.
      mSquigglyShot.explode();
    } else if (mSquigglyShot.collides(mAvatarLaser)) {
      // explode at the collision.
      mSquigglyShot.setEnabled(false);
      mSquigglyShot.setVisible(false);
      mAvatarLaser.explode();
    } else {
      // TODO handle collisions with the shields.
    }
  }

  // hide the flying saucer if it has travelled all across the screen.
  if (mFlyingSaucer.isVisible()) {
    if (mFlyingSaucer.getDirectionX() > 0.f) {
      if (mRightOobDetector.collides(mFlyingSaucer)) {
        mFlyingSaucer.setEnabled(false);
        mFlyingSaucer.setVisible(false);
      }
    } else {
      if (mLeftOobDetector.collides(mFlyingSaucer)) {
        mFlyingSaucer.setEnabled(false);
        mFlyingSaucer.setVisible(false);
      }
    }
  }
}

void IngameState::render(SDL_Renderer& renderer)
{
  mGameOverText.render(renderer);
  mFooterLine.render(renderer);
  mAvatar.render(renderer);
  mAvatarLaser.render(renderer);
  mFlyingSaucer.render(renderer);
  mLifesText.render(renderer);
  mLifeSprite1.render(renderer);
  mLifeSprite2.render(renderer);
  for (auto& alien : mAliens) {
    alien->render(renderer);
  }
  mPlungerShot.render(renderer);
  mSquigglyShot.render(renderer);
  mRollingShot.render(renderer);
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