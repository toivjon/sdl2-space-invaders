# sdl2-space-invaders
A SDL2 implementation of the classic Space Invaders game.

This implementation supports one and two players.

## Scenes
Game is split into following scenes:
1. A welcome scene, which contains the main menu and score descriptions.
2. A "play player" scene, which tells which player should prepare to play.
3. An in-game scene, which contains the actual gameplay.

The list of scene transitions:
* 1 to 2, when the number of players has been selected.
* 2 to 3, after 150 ticks.
* 3 to 2, after a level has been cleared i.e. all aliens has been destroyed.
* 3 to 2, after player has been killed and other player has still lives left (multiplayer only).
* 3 to 1, after pressing the enter key when game over text is being shown.

## Features
This Space Invaders implementation contains the following features:
* A support for one or two player (turn-based) games.
* Each player has three lives.
* Each level lasts until avatar or all aliens are destroyed or if any of the aliens invades.
* Game ends after each player has lost their lives.
* Player game state is stored when toggling between players in the two player mode.
* Aliens may shoot three different kind of missiles (rolling, plunger and squiggly).
* Plunger and squiggly alien shots follow predefined shoot patterns.
* Rolling shot is always launched from the players nearest alien.
* Game field contains four pixelwise destructable shields.
* Players earn points based on the destructed alien type.
* Alien movement speed is increased after the number of shown aliens decreases.
* Alien missile fire rate depends on the player score.
* Alien starting y-position depends on the level number.
* Flying saucer will be shown about periodically after each ~1200 ticks.
* Points received from the flying saucer is based on a lookup-table and player shot count.

## External Dependencies
This implementation has external dependencies on the following libraries:
* SDL2
* SDL2_ttf
* SDL2_image
* libfreetype-6.dll
* zlib1.dll
* libpng16-16.dll

## Compilation
Easiest way to compile the code is to use the [CMake](https://cmake.org/) utility.

Required tools and libraries for the compilation:
1. [CMake](https://cmake.org/) (ver. >=3.7.2)
2. [SDL2](https://www.libsdl.org/download-2.0.php) (ver. >=2.0.5)
3. [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (ver. >=2.0.14)
4. [SDL2_image] (https://www.libsdl.org/projects/SDL_image/) (ver. >= 2.0.2)
5. A compilation toolkit supported by the CMake utility (e.g. Visual Studio).

CMake compilation uses Find*-modules from the /cmake folder which specify where CMake looks for the required libraries.

Without any modifications, CMake will make use the following environment variable paths.
* SDL2DIR, which should point to the root directory of the SDL2 library.
* SDL2TTFDIR, which should point to the root directory of the SDL2_ttf library.
* SDL2IMAGEDIR, which should point to the root directory of the SDL2_image library.

## Screenshots
![alt text](https://github.com/toivjon/sdl2-space-invaders/blob/master/screenshots/welcome-scene.png "WelcomeScene")
![alt text](https://github.com/toivjon/sdl2-space-invaders/blob/master/screenshots/playplayer-scene.png "PlayerPlayerScene")
![alt text](https://github.com/toivjon/sdl2-space-invaders/blob/master/screenshots/ingame-scene.png "IngameScene")