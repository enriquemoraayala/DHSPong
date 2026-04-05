# Project Structure Guide

This document explains how the `DHSPong` project is organized so you can find the important code quickly and understand how the game is assembled.

## What This Project Is

`DHSPong` is a small Sega Mega Drive / Genesis game prototype built with **SGDK** in **C**.

The code is organized around:

- A main game loop in `src/main.c`
- A global game state stored in `Game game`
- Separate modules for logo, menu, gameplay, players, ball movement, coins, and collision helpers
- SGDK resource definition files in `res/*.res` that expose graphics, sprites, and audio to the C code

## Top-Level Folders

### `src/`

Contains the main game logic written by hand.

- `main.c`: Program entry point and main loop.
- `game.c`: Core game setup, input reading, main gameplay update, and drawing orchestration.
- `menu.c`: Main menu state and menu selector behavior.
- `logo.c`: Intro logo screen timing and transition to the menu.
- `player.c`: Paddle movement, paddle collision zones, and player drawing.
- `ball.c`: Ball launch, ball movement, wall/paddle collisions, scoring, sound triggers, and restart logic.
- `coins.c`: Coin spawning, movement, visibility, and coin sprite handling.
- `physics.c`: Generic collision helpers and screen boundary checks.
- `boot/`: Low-level startup files required by SGDK.

### `inc/`

Contains the project headers, shared constants, and public data structures.

- `game.h`: Main shared types like `Game`, `Ball`, `Coin`, `MenuStruct`, state enum, and function declarations for the game modules.
- `player.h`: `Player` struct, input enum, player mode enum, and player-related functions.
- `physics.h`: Collision constants, playfield dimensions, collider struct, and physics function declarations.
- `globals.h`: High-level gameplay constants such as initial paddle and ball positions.

### `res/`

Contains all game resources and SGDK resource declarations.

- `gfx/`: Background-style images like the table, logo, menu, and game over screen.
- `sprt/`: Sprite sheets for paddles, ball, markers, menu selector, impact animation, and coins.
- `sound/`: WAV files used for collisions and goals.
- `gfx.res`: Declares background image resources for SGDK.
- `sprt.res`: Declares sprite and palette resources for SGDK.
- `sound.res`: Declares WAV sound resources for SGDK.
- `gfx.h`, `sprt.h`, `sound.h`: Generated-style headers exposing those resources to the C code.

### `out/`

Build output directory.

This contains generated object files and dependency files such as:

- `out/src/*.o`, `out/src/*.d`
- `out/res/*.o`, `out/res/*.d`
- boot/build artifacts like `out/rom_head.o`

You usually do not edit anything here by hand.

### `.vscode/`

Editor configuration for Visual Studio Code.

- `launch.json`: Debug/run configuration
- `settings.json`: Workspace settings

## Runtime Flow

The game is driven by a simple state machine.

### 1. Startup

`src/main.c` starts the system, initializes SGDK systems, and sets:

- screen width
- input handling
- sound volume
- sprite engine
- initial state: `INIT_LOGO`

### 2. Main Loop

Every frame, `main()` runs:

1. `checkInputs()`
2. `update()`
3. `draw()`
4. `SPR_update()`
5. `SYS_doVBlankProcess()`

This is the core frame loop of the game.

### 3. State Machine

The active state lives in `game.state`, declared in `inc/game.h`.

States:

- `INIT_LOGO`
- `LOGO`
- `INIT_MENU`
- `MENU`
- `INIT_GAME`
- `LOOP_GAME`
- `GAME_OVER`
- `PAUSE`

The flow currently looks like this:

`INIT_LOGO` -> `LOGO` -> `INIT_MENU` -> `MENU` -> `INIT_GAME` -> `LOOP_GAME` -> `GAME_OVER`

## Important Shared Structures

### `Game`

Defined in `inc/game.h`.

This is the main global container for the current match:

- `player1`
- `player2`
- `ball`
- `state`
- `lastScored`
- `singlePlayer`

There is a single global instance declared in `src/game.c`:

```c
Game game;
```

Many modules read or modify this global object directly.

### `Player`

Defined in `inc/player.h`.

Represents a paddle/player and contains:

- sprite pointers
- position
- score
- current input
- player mode
- hit counter
- active coin tracking

### `Ball`

Defined in `inc/game.h`.

Tracks:

- sprite pointer
- impact sprite pointer
- position
- velocity
- launch state
- collision/sound flags

### `Coin`

Defined in `inc/game.h`.

Represents temporary coin pickups with:

- sprite pointer
- position
- velocity values
- active flag

`game.h` also declares a file-scope static array:

```c
static Coin coins[MAX_COINS];
```

That means coin storage is shared through the header, which is unusual and worth remembering when navigating the code.

## What Each Source File Does

### `src/main.c`

This file is the orchestrator.

Responsibilities:

- initializes SGDK systems
- polls input for both players
- routes control to the correct update/draw function based on `game.state`

If you want to understand the high-level flow first, start here.

### `src/game.c`

This is the central gameplay coordinator.

Responsibilities:

- defines the global `game`
- reads joypad input through `checkInput()`
- provides simple AI input through `iaInput()`
- initializes game variables in `initGame()`
- runs the gameplay update with `updateGame()`
- draws the gameplay scene with `drawGame()`
- handles game over transitions

This file connects the player, ball, and coin systems together.

### `src/logo.c`

Handles the intro/logo sequence.

Responsibilities:

- reset intro timer
- draw the logo image
- count frames
- transition to the menu after a delay

### `src/menu.c`

Handles the mode selection menu.

Responsibilities:

- initialize menu flags
- draw the menu background
- create menu selector sprites
- switch between one-player and two-player selection
- start the match when `START` is pressed

### `src/player.c`

Handles paddle movement and paddle-specific collision regions.

Responsibilities:

- move paddles up/down
- stop paddles from leaving the playfield
- detect where the ball touched the paddle
- update paddle and score marker sprite positions

The `isTouchingPaddle()` function is especially important because it splits the paddle into regions that change the bounce result.

### `src/ball.c`

Contains most of the match logic.

Responsibilities:

- launch the ball
- move the ball each frame
- bounce on top/bottom walls
- detect goals on left/right edges
- update scores
- reset positions after a goal
- trigger sounds
- spawn an impact animation
- notify the coin system after paddle hits

If you want to understand the actual Pong gameplay behavior, this is the key file.

### `src/coins.c`

Handles temporary coin entities.

Responsibilities:

- create coin sprites
- activate the next available coin
- hide coins
- move active coins according to the owning player
- draw active coins

This system looks partially implemented, so it is useful to read alongside `src/ball.c`.

### `src/physics.c`

Small utility module for collision logic.

Responsibilities:

- rectangle-vs-rectangle collision
- top/bottom boundary checks
- left/right goal boundary checks

This file is used by both player and ball logic.

### `src/boot/rom_head.c` and `src/boot/sega.s`

Low-level boot files used by SGDK for ROM startup and system metadata.

These are part of the platform setup rather than gameplay logic.

## Header Relationships

The headers define the shared vocabulary of the project:

- `game.h` depends on `player.h` and `physics.h`
- `player.h` depends on `physics.h`
- `main.c` includes `game.h` and `player.h`
- gameplay files include `game.h` to access the global `game` state
- resource-using files include `gfx.h`, `sprt.h`, and `sound.h`

In practice, `game.h` is the main "hub" header for the gameplay code.

## Resources And How They Connect To Code

The `.res` files are SGDK resource declaration files.

They map asset files to names used in C:

- `res/gfx.res` exposes images like `table`, `menu`, `over`, `logo`
- `res/sprt.res` exposes sprite definitions like `bat1`, `ball`, `menuSel`, `coin`
- `res/sound.res` exposes sounds like `bounce`, `goal`, `playerhit`

Then the C code includes:

- `gfx.h`
- `sprt.h`
- `sound.h`

and uses those identifiers directly with SGDK functions such as:

- `VDP_drawImageEx(...)`
- `SPR_addSprite(...)`
- `PAL_setPalette(...)`
- `XGM2_playPCM(...)`

## Files You’ll Most Likely Read First

If your goal is to understand the code quickly, this order works well:

1. `src/main.c`
2. `inc/game.h`
3. `src/game.c`
4. `src/ball.c`
5. `src/player.c`
6. `src/menu.c`
7. `src/physics.c`
8. `res/*.res`

That path gives you the control flow first, then the data structures, then the gameplay rules.

## Notes About The Current Structure

A few structural details are worth keeping in mind:

- The project relies heavily on global state through `game`.
- State transitions are split between update and draw functions.
- Some resource headers are part of the asset pipeline rather than handwritten gameplay code.
- The coin system appears incomplete or experimental.
- `out/` contains generated build files and is not part of the gameplay source structure.

## Suggested Mental Model

You can think of the project in four layers:

1. **Platform layer**: SGDK boot files and SGDK APIs
2. **Resources layer**: images, sprites, sounds, and `.res` declarations
3. **Core gameplay layer**: `game`, `player`, `ball`, `physics`, `coins`
4. **Flow layer**: state machine in `main.c` controlling logo, menu, game, and game over

If you keep those four layers in mind while reading, the repository becomes much easier to navigate.
