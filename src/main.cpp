/*! The entry point of the application.
*
* This is the entry point for an old legendary Space Invaders game implemented
* with the SDL2 library. This entry point contains a simple logic where we only
* create, start and close the application as required. See the other files for
* more interesting details how the actual game is implemented.
*/
#include "game.h"

using namespace space_invaders;

int main(int argc, char* args[])
{
  Game game(672, 768);
  return game.run();
}