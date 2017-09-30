/*! An abstraction of all scenes within the Space Invaders application.
 * 
 * Our implementation of the Space Invaders contains only a single scene,
 * which has three different states available to shown to users. States are
 * also used to navigate and switch between players in the multiplayer mode.
 */
#ifndef SPACE_INVADERS_SCENE_H
#define SPACE_INVADERS_SCENE_H

#include "state.h"
#include <memory>

// forward declarations in the global namespace.
struct SDL_Renderer;
struct SDL_KeyboardEvent;

namespace space_invaders
{
  class TextEntity;
  class Game;
  class Scene
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    Scene() = delete;
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) = delete;
    
    // =====================
    // = allowed functions =
    // =====================

    Scene(Game& game);
    ~Scene() = default;

    void update(unsigned long dt);
    void render(SDL_Renderer& renderer);

    void onKeyUp(SDL_KeyboardEvent& event);
    void onKeyDown(SDL_KeyboardEvent& event);

    void setState(StatePtr state);
  protected:
    Game&     mGame;
    StatePtr  mState;

    std::shared_ptr<TextEntity> mScore1Caption;
    std::shared_ptr<TextEntity> mHiScoreCaption;
    std::shared_ptr<TextEntity> mScore2Caption;

    std::shared_ptr<TextEntity> mScore1Text;
    std::shared_ptr<TextEntity> mHiScoreText;
    std::shared_ptr<TextEntity> mScore2Text;
  };
  typedef std::shared_ptr<Scene> ScenePtr;
}

#endif