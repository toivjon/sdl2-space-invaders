#include "alien_shot.h"
#include "game.h"
#include "player_context.h"

using namespace space_invaders;

AlienShot::AlienShot(Game& game) : AnimatedEntity(game), mProgressTicks(0)
{
  // ...
}

void AlienShot::update(unsigned long dt)
{
  if (isVisible()) {
    AnimatedEntity::update(dt);
    mProgressTicks++;
  }
}

void AlienShot::fire()
{
  setEnabled(true);
  setVisible(true);
  setCurrentAnimation("normal");
  setDirectionY(1.f);
  mProgressTicks = 1;
}

void AlienShot::explode()
{
  setEnabled(false);
  setCurrentAnimation("explode");
  setDisappearCountdown(10);
  setDirectionY(0.f);
}

bool AlienShot::isReadyToBeFired(const AlienShot& shot1, const AlienShot& shot2) const
{
  // shot cannot be re-fired while in progress.
  if (isVisible() == true) {
    return false;
  }

  // resolve the current reload rate for the aliens.
  const auto reloadRate = getReloadRate();
  
  // check whether it's too soon to fire again.
  if (shot1.mProgressTicks > 0 && reloadRate >= shot1.mProgressTicks) {
    return false;
  } else if (shot2.mProgressTicks > 0 && reloadRate >= shot2.mProgressTicks) {
    return false;
  }

  // it seems that it's ok to fire again.
  return true;
}

int AlienShot::getReloadRate() const
{
  // get a reference to the current score.
  const auto& ctx = mGame.getActivePlayerContext();
  const auto currentScore = ctx.getScore();

  // return a reload rate based on the current score.
  if (currentScore <= 200) {
    return 48;
  } else if (currentScore <= 1000) {
    return 16;
  } else if (currentScore <= 2000) {
    return 11;
  } else if (currentScore <= 3000) {
    return 8;
  } else {
    return 7;
  }
}