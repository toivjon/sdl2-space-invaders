#include "alien_shot.h"
#include "game.h"
#include "player_context.h"
#include "ingame_state.h"

using namespace space_invaders;

AlienShot::AlienShot(Game& game, IngameState& state) : AnimatedEntity(game), mState(state), mProgressTicks(0)
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

bool AlienShot::isReadyToBeFired() const
{
  // shot cannot be re-fired while in progress.
  if (isVisible() == true) {
    return false;
  }

  // resolve the current reload rate for the aliens.
  const auto reloadRate = getReloadRate();
  
  // get a reference to each alien shot within the state.
  const auto& rollingShot = mState.getRollingShot();
  const auto& plungerShot = mState.getPlungerShot();
  const auto& squigglyShot = mState.getSquigglyShot();

  // check whether it's too soon to fire again.
  if (this != &rollingShot && rollingShot.mProgressTicks > 0 && reloadRate >= rollingShot.mProgressTicks) {
    return false;
  } else if (this != &plungerShot && plungerShot.mProgressTicks > 0 && reloadRate >= plungerShot.mProgressTicks) {
    return false;
  } else if (this != &squigglyShot && squigglyShot.mProgressTicks > 0 && reloadRate >= squigglyShot.mProgressTicks) {
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