/*! The container that holds player specific data and state.
 *
 * Space invaders contains a support for single- and multiplayer game modes. It
 * is a good idea to store player specific data in a special container called a
 * context. It contians all player specific data, which helps us to keep player
 * data in a centralized place and also helps us to reconstruct the game state
 * when the player switch is requested after a player destruction in the game.
 */
#ifndef SPACE_INVADER_PLAYER_CONTEXT_H
#define SPACE_INVADER_PLAYER_CONTEXT_H

namespace space_invaders
{
  class PlayerContext
  {
  public:
    // ===============================
    // = forbidden default functions =
    // ===============================

    PlayerContext(const PlayerContext&) = delete;
    PlayerContext(PlayerContext&&) = delete;
    PlayerContext& operator=(const PlayerContext&) = delete;
    PlayerContext& operator=(PlayerContext&&) = delete;

    // =====================
    // = allowed functions =
    // =====================

    PlayerContext();

    void addScore(int score) { mScore += score; }

    void setLevel(int level) { mLevel = level; }
    void setScore(int score) { mScore = score; }
    void setLives(int lives) { mLives = lives; }

    int getLevel() const { return mLevel; }
    int getScore() const { return mScore; }
    int getLives() const { return mLives; }
  private:
    int mLevel;
    int mScore;
    int mLives;
    // TODO alien states.
    // TODO shield states.
  };
}

#endif