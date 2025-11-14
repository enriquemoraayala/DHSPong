#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>
#include "player.h"

typedef enum state
{
    INIT_MENU,
    MENU,
    INIT_GAME,
    LOOP_GAME,
    GAME_OVER,
    PAUSE

} Status;

typedef struct
{
    Sprite *sprite;
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
    bool launched;
    bool impact;
} Ball;

typedef struct
{
    Player player1;
    Player player2;
    Ball ball;
    Status state;
    bool singlePlayer;
} Game;

extern Game game;

void initGame();

Input checkInput(u16);

void updateGame();

void drawGame();

void drawInitGame();

#endif
