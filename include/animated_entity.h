/*! An abstraction for all movalbe sprite entities that can be animated.
 *
 * This structure contains the logics required to make an movable entity to be
 * animated. Animation can be used in two different modes:
 *
 * 1. Automatically animated mode.
 * 2. Manually animated mode.
 *
 * Automatically animated mode is where the entity is automatically animated
 * when enough animation steps has passed. Manually animated mode will only
 * act as a placeholder for multiple sprites that must be manually assigned to
 * make the sprite image to change.
*/
#ifndef SPACE_INVADERS_ANIMATED_ENTITY_H
#define SPACE_INVADERS_ANIMATED_ENTITY_H

#include "movable_entity.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace space_invaders
{
  class AnimatedEntity : public MovableEntity
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    AnimatedEntity() = delete;
    AnimatedEntity(const AnimatedEntity&) = delete;
    AnimatedEntity(AnimatedEntity&&) = delete;
    AnimatedEntity& operator=(const AnimatedEntity&) = delete;
    AnimatedEntity& operator=(AnimatedEntity&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    AnimatedEntity(Game& game);
    ~AnimatedEntity() override = default;

    void update(unsigned long dt) override;

    void setAnimationStepSize(int stepSize);
    void setCurrentAnimation(const std::string& name);
    void setAnimationFrame(unsigned int frameIndex);
    void addAnimationFrame(const std::string& name, const SDL_Rect& rect);
  private:
    int mAnimationStepSize;
    int mAnimationCounter;
    int mAnimationFrameIndex;

    std::vector<SDL_Rect> mCurrentAnimation;
    std::unordered_map<std::string, std::vector<SDL_Rect>> mAnimations;
  };
}

#endif