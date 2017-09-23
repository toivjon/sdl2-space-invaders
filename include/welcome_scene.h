#ifndef SPACE_INVADERS_WELCOME_SCENE_H
#define SPACE_INVADERS_WELCOME_SCENE_H

#include "scene.h"

namespace space_invaders
{
  class WelcomeScene final : public Scene
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    WelcomeScene() = delete;
    WelcomeScene(const WelcomeScene&) = delete;
    WelcomeScene(WelcomeScene&&) = delete;
    WelcomeScene& operator=(const WelcomeScene&) = delete;
    WelcomeScene& operator=(WelcomeScene&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    WelcomeScene(Game& game);
    ~WelcomeScene() override;

    void enter() override;
    void exit() override;

    void update(unsigned long dt) override;
    void render(SDL_Renderer& renderer) override;

    void onKeyUp(SDL_KeyboardEvent& event) override;
    void onKeyDown(SDL_KeyboardEvent& event) override;
  };
}

#endif