#include "rolling_shot.h"
#include "game.h"
#include "ingame_state.h"

#include <algorithm>

using namespace space_invaders;

RollingShot::RollingShot(Game& game, IngameState& state) : AlienShot(game, state), mLock(0)
{
  setImage(mGame.getSpriteSheet());
  setWidth(9);
  setHeight(21);
  setVelocity(0.2f);
  setDirectionY(1.f);
  addAnimationFrame("normal", { 149, 37, 9, 21 });
  addAnimationFrame("normal", { 163, 37, 9, 21 });
  addAnimationFrame("normal", { 149, 37, 9, 21 });
  addAnimationFrame("normal", { 178, 37, 9, 21 });
  addAnimationFrame("explode", { 218, 5, 18, 24 });
  setCurrentAnimation("normal");
  setAnimationStepSize(4);
  setVisible(false);
  setEnabled(false);
}

void RollingShot::update(unsigned long dt)
{
  if (mLock > 0) {
    mLock--;
  }
  AlienShot::update(dt);
}

void RollingShot::fire()
{
  // get a reference to the player avatar and aliens.
  const auto& avatar = mState.getAvatar();
  const auto& aliens = mState.getAliens();

  // resolve the nearest active alien from the list.
  const auto avatarX = avatar.getX();
  auto alienIdx = -1;
  auto prevDistance = -1;
  for (auto col = 0; col < 11; col++) {
    auto distance = std::abs(aliens[col]->getCenterX() - avatarX);
    if (prevDistance != -1 && distance > prevDistance) {
      break;
    } else {
      for (auto row = 4; row >= 0; row--) {
        auto idx = (row * 11) + col;
        if (aliens[col]->isVisible()) {
          alienIdx = idx;
          prevDistance = distance;
          break;
        }
      }
    }
  }

  // shoot if we found a suitable alien.
  if (alienIdx != -1) {
    auto alien = aliens[alienIdx];
    setX(alien->getCenterX() - getExtentX());
    setY(alien->getY() + alien->getHeight());
    AlienShot::fire();
    mLock = getReloadRate() * 4;
  }
}