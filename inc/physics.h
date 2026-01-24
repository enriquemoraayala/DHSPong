#ifndef _H_PHYSICS
#define _H_PHYSICS
#include <genesis.h>

#define PLAYER_SPEED 3
#define BALL_SPEED 4
#define BALL_MAX_SPEED 8
#define BALL_OFFSET 8
#define BALL_DIAMETRE 16

#define PADDEL_OFFSET_WIDTH 11
#define PADDLE_OFFSET_HEIGTH 3

#define PADDLE_WIDTH 9
#define PADDLE_HEIGTH 58

#define PADDLE_EXTREME_WIDTH 8
#define PADDLE_EXTREME_HEIGTH 4

#define TOP_EDGE 0
#define TOP_EDGE_Y 0
#define EDGE_WIDTH 320
#define EDGE_HEIGHT 8
#define BOTTOM_EDGE 0
#define BOTTOM_EDGE_Y 216

#define LATERAL_EDGE_WIDTH 8
#define LATERAL_EDGE_HEIGHT 224
#define LATERAL_EDGE 312

#define MAX_COINS 2
#define COIN_SPEED FIX16(2)   // px por frame aprox
#define COIN_TTL 260        // frames (3s a 60fps)

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} BoxCollider;

#define CHANGE_SIGN(n) -n

bool isColliding(BoxCollider *, BoxCollider *);
bool isTouchingTop(u16, u16, u16, u16);
bool isTouchingBottom(u16, u16, u16, u16);
bool isTouchingLeftEdge(u16, u16, u16, u16);
bool isTouchingRightEdge(u16, u16, u16, u16);

#endif