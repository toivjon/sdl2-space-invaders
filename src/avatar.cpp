#include "avatar.h"
#include "game.h"
#include "player_context.h"

using namespace space_invaders;

Avatar::Avatar(Game& game) : AnimatedEntity(game)
{
  setImage(game.getSpriteSheet());
  addAnimationFrame("still", { 86, 5, 40, 24 });
  addAnimationFrame("explosion", { 128, 91, 45, 24 });
  addAnimationFrame("explosion", { 178, 91, 45, 24 });
  setCurrentAnimation("still");
  setX(getWidth() / 2);
  setY(648);
  setVelocity(0.25f);
}

void Avatar::explode()
{
  // stop and disable the movement of the avatar.
  setDirectionX(0.f);
  setEnabled(false);

  // start the explosion animation for the avatar.
  setCurrentAnimation("explosion");
  setAnimationStepSize(6);
  setDisappearCountdown(48);

  // decrement lives and start the scene relaunch counter.
  auto& ctx = mGame.getActivePlayerContext();
  ctx.setLives(ctx.getLives() - 1);
  ctx.setRelaunchTimer(150);
}

void Avatar::reset()
{
  // reset the starting position of the avatar.
  setX(getWidth() / 2);

  // set avatar back to collideable and visible.
  setEnabled(true);
  setVisible(true);

  // reset the visual presentation of the avatar.
  setCurrentAnimation("still");
}