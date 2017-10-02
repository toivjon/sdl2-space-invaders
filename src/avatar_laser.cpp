#include "avatar_laser.h"
#include "game.h"

using namespace space_invaders;

AvatarLaser::AvatarLaser(Game& game) : AnimatedEntity(game)
{
  setImage(game.getSpriteSheet());
  addAnimationFrame("normal", { 80, 36, 6, 9 });
  addAnimationFrame("top-wall-hit", { 131, 5, 39, 24 });
  addAnimationFrame("alien-hit", { 175, 5, 39, 24 });
  addAnimationFrame("alien-laser-hit", { 251, 37, 24, 24 });
  setCurrentAnimation("normal");
  setX(0);
  setY(0);
  setVelocity(0.75f);
  setDirectionY(-1.f);
  setVisible(false);
  setEnabled(false);
}

void AvatarLaser::explode()
{
  setAnimationStepSize(0);
  setAnimationFrame(0);
  setEnabled(false);
  setDisappearCountdown(10);
  setDirectionY(0);
}