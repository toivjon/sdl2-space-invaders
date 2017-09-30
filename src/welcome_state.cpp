#include "welcome_state.h"

using namespace space_invaders;

WelcomeState::WelcomeState(Game& game) : State(game),
  mPlayText(game),
  mNameText(game),
  mSinglePlayerText(game),
  mMultiPlayerText(game),
  mControlsText(game),
  mTableCaptionText(game)
{
  // initialize the play game text.
  mPlayText.setText("PLAY");
  mPlayText.setX(672 / 2 - mPlayText.getWidth() / 2);
  mPlayText.setY(175);

  // initialize the game name text.
  mNameText.setText("SDL2 SPACE INVADERS");
  mNameText.setColor({ 32, 255, 32, 255 });
  mNameText.setX(672 / 2 - mNameText.getWidth() / 2);
  mNameText.setY(mPlayText.getY() + 75);

  // initialize the single player text.
  mSinglePlayerText.setText("PRESS [1] FOR A 1 PLAYER GAME");
  mSinglePlayerText.setX(672 / 2 - mSinglePlayerText.getWidth() / 2);
  mSinglePlayerText.setY(mNameText.getY() + 75);
  mSinglePlayerText.setBlinkCount(-1);
  mSinglePlayerText.setBlinkFrequency(30);
  mSinglePlayerText.blink();

  // initialize the multiplayer text.
  mMultiPlayerText.setText("PRESS [2] FOR A 2 PLAYER GAME");
  mMultiPlayerText.setX(672 / 2 - mSinglePlayerText.getWidth() / 2);
  mMultiPlayerText.setY(mSinglePlayerText.getY() + 50);
  mMultiPlayerText.setBlinkCount(-1);
  mMultiPlayerText.setBlinkFrequency(30);
  mMultiPlayerText.blink();

  // initialize the controls description text.
  mControlsText.setText("USE ARROW KEYS AND SPACEBAR TO PLAY");
  mControlsText.setX(672 / 2 - mControlsText.getWidth() / 2);
  mControlsText.setY(mMultiPlayerText.getY() + 75);

  // initialize the score advance table text.
  mTableCaptionText.setText("--- SCORE ADVANCE TABLE ---");
  mTableCaptionText.setX(672 / 2 - mTableCaptionText.getWidth() / 2);
  mTableCaptionText.setY(mControlsText.getY() + 75);
}

void WelcomeState::update(unsigned long dt)
{
  mPlayText.update(dt);
  mNameText.update(dt);
  mSinglePlayerText.update(dt);
  mMultiPlayerText.update(dt);
  mControlsText.update(dt);
  mTableCaptionText.update(dt);
}

void WelcomeState::render(SDL_Renderer& renderer)
{
  mPlayText.render(renderer);
  mNameText.render(renderer);
  mSinglePlayerText.render(renderer);
  mMultiPlayerText.render(renderer);
  mControlsText.render(renderer);
  mTableCaptionText.render(renderer);
}

void WelcomeState::onEnter()
{

}

void WelcomeState::onExit()
{

}

void WelcomeState::onKeyUp(SDL_KeyboardEvent& event)
{
  
}

void WelcomeState::onKeyDown(SDL_KeyboardEvent& event)
{

}