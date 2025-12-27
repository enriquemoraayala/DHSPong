#ifndef _H_PLAYER
#define _H_PLAYER
#include <genesis.h>

typedef enum player_mode
{
    IA,
    PLAYER
} PlayerMode;

typedef enum input
{
    UP,
    DOWN,
    START,
    A,
    NONE
} Input;

typedef struct
{
    Sprite *sprite;
    Sprite *marc;
    u16 x;
    u16 y;
    s16 score;
    Input input;
    PlayerMode playerMode;
} Player;

void initPlayer(Player *, u16, u16, PlayerMode);

void updatePlayer(Player *);

void drawPlayer(Player *);

s8 isTouchingPaddle(Player*, u16, u16, u16, u16);

#endif