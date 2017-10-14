#include "squiggly_shot.h"
#include "game.h"
#include "ingame_state.h"

using namespace space_invaders;

const std::array<int, 15> SquigglyShot::SHOT_COLUMNS = {
  10, 0, 5, 2, 0, 0, 10, 8, 1, 7, 1, 10, 3, 6, 9
};

SquigglyShot::SquigglyShot(Game& game, IngameState& state) : AlienShot(game, state), mNextShotColumnIndex(0)
{
  setImage(mGame.getSpriteSheet());
  setWidth(9);
  setHeight(21);
  setVelocity(0.2f);
  setDirectionY(1.f);
  addAnimationFrame("normal", { 191, 37, 9, 21 });
  addAnimationFrame("normal", { 206, 37, 9, 21 });
  addAnimationFrame("normal", { 221, 37, 9, 21 });
  addAnimationFrame("normal", { 236, 37, 9, 21 });
  addAnimationFrame("explode", { 218, 5, 18, 24 });
  setCurrentAnimation("normal");
  setAnimationStepSize(4);
  setVisible(false);
  setEnabled(false);
}

void SquigglyShot::fire()
{
  // get the target column where this shot should be fired.
  const auto col = SHOT_COLUMNS[mNextShotColumnIndex];

  // increment the shot column to prepare for the next shot.
  mNextShotColumnIndex = ((mNextShotColumnIndex + 1) % SHOT_COLUMNS.size());

  // find the target alien to shoot the missile from.
  const auto& aliens = mState.getAliens();
  for (auto i = 4; i >= 0; i--) {
    auto index = (i * 11) + col;
    auto alien = aliens[index];
    if (alien->isVisible()) {
      // assign the position of the shot based on the nearest alien.
      setX(alien->getCenterX() - getExtentX());
      setY(alien->getY() + alien->getHeight());

      // ... go fire!
      AlienShot::fire();
      return;
    }
  }
}