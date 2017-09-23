/*! An abstraction of all scenes within the Space Invaders application.
 * 
 * Our implementation of the Space Invaders contains three different scenes
 * where each scene has typical game scene features, which are called when
 * the scene is either active or is being exited or entered. This abstraction
 * ensures that every scene will implement at least the required functions.
 */
#ifndef SPACE_INVADERS_SCENE_H
#define SPACE_INVADERS_SCENE_H

#include <memory>

// forward declarations in the global namespace.
struct SDL_Renderer;
struct SDL_KeyboardEvent;

namespace space_invaders
{
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

    Scene(Game& game) : mGame(game) {}
    virtual ~Scene() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;

    virtual void update(unsigned long dt) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;

    virtual void onKeyUp(SDL_KeyboardEvent& event) = 0;
    virtual void onKeyDown(SDL_KeyboardEvent& event) = 0;
  protected:
    Game& mGame;
  };
  typedef std::shared_ptr<Scene> ScenePtr;
}

#endif