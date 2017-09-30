#include "scene.h"
#include "game.h"
#include "text_entity.h"

using namespace space_invaders;

inline std::string toScoreString(int score) {
  auto result = std::to_string(score);
  auto difference = (4 - result.size());
  if (difference >= 0) {
    result = "0000" + result;
  }
  return result.substr(result.length() - 4, 4);
}

Scene::Scene(Game& game) : mGame(game),
  mScore1Caption(std::make_shared<TextEntity>(game)),
  mHiScoreCaption(std::make_shared<TextEntity>(game)),
  mScore2Caption(std::make_shared<TextEntity>(game)),
  mScore1Text(std::make_shared<TextEntity>(game)),
  mHiScoreText(std::make_shared<TextEntity>(game)),
  mScore2Text(std::make_shared<TextEntity>(game))
{
  // initialize the static caption for the 1st player score.
  mScore1Caption->setText("SCORE<1>");
  mScore1Caption->setX(125 - (mScore1Caption->getWidth() / 2));
  mScore1Caption->setY(40);

  // initialize the static caption for the high score.
  mHiScoreCaption->setText("HI-SCORE");
  mHiScoreCaption->setX(672 / 2 - (mHiScoreCaption->getWidth() / 2));
  mHiScoreCaption->setY(mScore1Caption->getY());

  // initialize the static caption for the 2nd player score.
  mScore2Caption->setText("SCORE<2>");
  mScore2Caption->setX(672 - 130 - (mScore2Caption->getWidth() / 2));
  mScore2Caption->setY(mScore1Caption->getY());

  // initialize the dynamic score value for the 1st player.
  mScore1Text->setText("0000");
  mScore1Text->setX(125 - (mScore1Text->getWidth() / 2));
  mScore1Text->setY(mScore1Caption->getY() + 35);

  // initialize the dynamic score value for the high score.
  mHiScoreText->setText("0000");
  mHiScoreText->setX(672 / 2 - (mHiScoreText->getWidth() / 2));
  mHiScoreText->setY(mScore1Text->getY());

  // initialize the dynamic score value for the 2nd player.
  mScore2Text->setText("0000");
  mScore2Text->setX(672 - 130 - (mScore2Text->getWidth() / 2));
  mScore2Text->setY(mScore1Text->getY());
}

void Scene::update(unsigned long dt)
{
  // TODO ensure player 1 score validity.
  // TODO ensure player 2 score validity.

  mScore1Caption->update(dt);
  mHiScoreCaption->update(dt);
  mScore2Caption->update(dt);

  mScore1Text->update(dt);
  mHiScoreText->update(dt);
  mScore2Text->update(dt);

  // TODO update the current state.
}

void Scene::render(SDL_Renderer& renderer)
{
  mScore1Caption->render(renderer);
  mHiScoreCaption->render(renderer);
  mScore2Caption->render(renderer);

  mScore1Text->render(renderer);
  mHiScoreText->render(renderer);
  mScore2Text->render(renderer);

  // TODO render the current state.
}

void Scene::onKeyUp(SDL_KeyboardEvent& event)
{
  // TODO pass to current state.
}

void Scene::onKeyDown(SDL_KeyboardEvent& event)
{
  // TODO pass to current state.
}