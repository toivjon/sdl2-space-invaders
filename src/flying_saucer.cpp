#include "flying_saucer.h"
#include "game.h"
#include "player_context.h"

using namespace space_invaders;

const std::array<int, 15> FlyingSaucer::POINT_TABLE = {
  100, 50, 50, 100, 150, 100, 100, 50, 300, 100, 100, 100, 50, 150, 100
};

FlyingSaucer::FlyingSaucer(Game& game) 
  : AnimatedEntity(game),
    mAppearingCounter(APPEAR_INTERVAL)
{
  setImage(game.getSpriteSheet());
  setVelocity(0.15f);
  setEnabled(false);
  setVisible(false);
  setX(672 - 43);
  setY(145);
  setWidth(43);
  setHeight(19);
  addAnimationFrame("normal", { 5, 91, 43, 19 });
  addAnimationFrame("explode", { 54, 91, 66, 24 });
  setCurrentAnimation("normal");
}

void FlyingSaucer::update(unsigned long dt)
{
  // decrement the flying saucer counter if the saucer is not yet visible.
  if (isVisible() == false) {
    mAppearingCounter--;
  } else {
    AnimatedEntity::update(dt);
  }
}

void FlyingSaucer::explode()
{
  setDirectionX(0);
  setCurrentAnimation("explode");
  setDisappearCountdown(15);
}

void FlyingSaucer::launch()
{
  // get the current shot count from the player context.
  const auto& ctx = mGame.getActivePlayerContext();
  const auto shotCount = ctx.getShotCount();

  // resolve the saucer movement direction based on the count.
  if ((shotCount % 2) == 0) {
    setDirectionX(-1.f);
    setX(672 - getWidth());
  } else {
    setDirectionX(1.f);
    setX(0);
  }

  // enable, show and reset the saucer timer.
  setEnabled(true);
  setVisible(true);
  setCurrentAnimation("normal");
  mAppearingCounter = APPEAR_INTERVAL;
}

int FlyingSaucer::getPoints() const
{
  // get the current shot count from the player context.
  const auto& ctx = mGame.getActivePlayerContext();
  const auto shotCount = ctx.getShotCount();

  // get points from the point table based on the shot count.
  return POINT_TABLE[shotCount % 15];
}