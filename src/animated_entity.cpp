#include "animated_entity.h"

#include <algorithm>

using namespace space_invaders;

AnimatedEntity::AnimatedEntity(Game& game)
  : MovableEntity(game),
    mAnimationStepSize(0),
    mAnimationCounter(0),
    mAnimationFrameIndex(0)
{
  // ...
}

void AnimatedEntity::update(unsigned long dt)
{
  MovableEntity::update(dt);
  if (mCurrentAnimation.size() > 1 && mAnimationStepSize > 0) {
    mAnimationCounter = std::max(0, mAnimationCounter - 1);
    if (mAnimationCounter <= 0) {
      auto nextFrame = ((mAnimationFrameIndex + 1) % mCurrentAnimation.size());
      setAnimationFrame(nextFrame);
      mAnimationCounter = mAnimationStepSize;
    }
  }
}

void AnimatedEntity::setAnimationStepSize(int stepSize)
{
  mAnimationStepSize = stepSize;
}

void AnimatedEntity::setCurrentAnimation(const std::string& name)
{
  if (mAnimations.find(name) != mAnimations.end()) {
    mCurrentAnimation = mAnimations[name];
    mAnimationCounter = mAnimationStepSize;
    setAnimationFrame(0);
  }
}

void AnimatedEntity::setAnimationFrame(unsigned int frameIndex)
{
  if (mCurrentAnimation.empty() == false) {
    // ensure that we are not exceeding animation limits.
    frameIndex = std::min(mCurrentAnimation.size(), frameIndex);

    // get a reference to the next frame dimensions.
    const auto& animationClip = mCurrentAnimation[frameIndex];

    // store current center x and y positions.
    auto centerX = getCenterX();
    auto centerY = getCenterY();

    // assign the new animation frame as the current frame.
    setClip(animationClip);

    // restore center x and y positions.
    setCenterX(centerX);
    setCenterY(centerY);

    // store the new index.
    mAnimationFrameIndex = frameIndex;
  }
}

void AnimatedEntity::addAnimationFrame(const std::string& name, const SDL_Rect& rect)
{
  // add a new animation frame container if not yet created.
  if (mAnimations.find(name) == mAnimations.end()) {
    mAnimations[name] = std::vector<SDL_Rect>();
  }

  // add the new animation frame into the container.
  mAnimations[name].push_back(rect);
}