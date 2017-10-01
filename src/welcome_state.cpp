#include "welcome_state.h"
#include "game.h"

using namespace space_invaders;

WelcomeState::WelcomeState(Game& game) : State(game),
  mPlayText(game),
  mNameText(game),
  mSinglePlayerText(game),
  mMultiPlayerText(game),
  mControlsText(game),
  mTableCaptionText(game),
  mTableRow1Text(game),
  mTableRow2Text(game),
  mTableRow3Text(game),
  mTableRow4Text(game),
  mTableRow1Sprite(game),
  mTableRow2Sprite(game),
  mTableRow3Sprite(game),
  mTableRow4Sprite(game)
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

  // initialize the 1st table row sprite image.
  mTableRow1Sprite.setImage(game.getSpriteSheet());
  mTableRow1Sprite.setClip({ 5, 92, 43, 19 });
  mTableRow1Sprite.setX(672 / 2 - 130);
  mTableRow1Sprite.setY(mTableCaptionText.getY() + 55);

  // initialize the 1st table row text.
  mTableRow1Text.setText("= ?  MYSTERY");
  mTableRow1Text.setX(mTableRow1Sprite.getX() + 10 + mTableRow1Sprite.getWidth());
  mTableRow1Text.setY(mTableRow1Sprite.getY() - 5);

  // initialize the 2nd table row sprite image.
  mTableRow2Sprite.setImage(game.getSpriteSheet());
  mTableRow2Sprite.setClip({ 5, 63, 24, 24 });
  mTableRow2Sprite.setX(672 / 2 - 120);
  mTableRow2Sprite.setY(mTableRow1Sprite.getY() + 35);

  // initialize the 2nd table row text.
  mTableRow2Text.setText("= 30 POINTS");
  mTableRow2Text.setX(mTableRow1Text.getX());
  mTableRow2Text.setY(mTableRow2Sprite.getY() - 5);

  // initialize the 3rd table row sprite image.
  mTableRow3Sprite.setImage(game.getSpriteSheet());
  mTableRow3Sprite.setClip({ 5, 34, 33, 24 });
  mTableRow3Sprite.setX(672 / 2 - 125);
  mTableRow3Sprite.setY(mTableRow2Sprite.getY() + 35);

  // initialize the 3rd table row text.
  mTableRow3Text.setText("= 20 POINTS");
  mTableRow3Text.setX(mTableRow1Text.getX());
  mTableRow3Text.setY(mTableRow3Sprite.getY() - 5);

  // initialize the 4th table row sprite image.
  mTableRow4Sprite.setImage(game.getSpriteSheet());
  mTableRow4Sprite.setClip({ 5, 5, 36, 24 });
  mTableRow4Sprite.setX(672 / 2 - 125);
  mTableRow4Sprite.setY(mTableRow3Sprite.getY() + 35);

  // initialize the 4th table row text.
  mTableRow4Text.setText("= 10 POINTS");
  mTableRow4Text.setX(mTableRow1Text.getX());
  mTableRow4Text.setY(mTableRow4Sprite.getY() - 5);
}

void WelcomeState::update(unsigned long dt)
{
  mPlayText.update(dt);
  mNameText.update(dt);
  mSinglePlayerText.update(dt);
  mMultiPlayerText.update(dt);
  mControlsText.update(dt);
  mTableCaptionText.update(dt);
  mTableRow1Text.update(dt);
  mTableRow2Text.update(dt);
  mTableRow3Text.update(dt);
  mTableRow4Text.update(dt);
  mTableRow1Sprite.update(dt);
  mTableRow2Sprite.update(dt);
  mTableRow3Sprite.update(dt);
  mTableRow4Sprite.update(dt);
}

void WelcomeState::render(SDL_Renderer& renderer)
{
  mPlayText.render(renderer);
  mNameText.render(renderer);
  mSinglePlayerText.render(renderer);
  mMultiPlayerText.render(renderer);
  mControlsText.render(renderer);
  mTableCaptionText.render(renderer);
  mTableRow1Text.render(renderer);
  mTableRow2Text.render(renderer);
  mTableRow3Text.render(renderer);
  mTableRow4Text.render(renderer);
  mTableRow1Sprite.render(renderer);
  mTableRow2Sprite.render(renderer);
  mTableRow3Sprite.render(renderer);
  mTableRow4Sprite.render(renderer);
}

void WelcomeState::onEnter()
{
  // ...
}

void WelcomeState::onExit()
{
  // ...
}

void WelcomeState::onKeyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_1:
    mGame.setPlayerCount(1);
    mGame.setActivePlayer(Game::Player::PLAYER_1);
    break;
  case SDLK_2:
    mGame.setPlayerCount(2);
    mGame.setActivePlayer(Game::Player::PLAYER_1);
    break;
  default:
    break;
  }
}

void WelcomeState::onKeyDown(SDL_KeyboardEvent& event)
{
  // ...
}