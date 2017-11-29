#include "player_context.h"

using namespace space_invaders;

PlayerContext::PlayerContext() : mLevel(1), mScore(0), mLives(3), mShotCount(0), mRelaunchTimer(0)
{
  // ...
}

void PlayerContext::reset()
{
  mLevel = 1;
  mScore = 0;
  mLives = 3;
  mShotCount = 0;
  mRelaunchTimer = 0;
  mAliens.clear();
  mShields.clear();
}