#ifndef _H_PHYSICS
#define _H_PHYSICS
#include <genesis.h>

#define PLAYER_SPEED 3
#define BALL_SPEED 4

#define PADDLE_WIDTH 8
#define PADDLE_HEIGTH 57

#define TOP_EDGE 0
#define TOP_EDGE_Y 0
#define EDGE_WIDTH 320
#define EDGE_HEIGHT 8
#define BOTTOM_EDGE 216
#define BOTTOM_EDGE_Y 0


typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} BoxCollider;

bool isColliding(BoxCollider *, BoxCollider *);
bool isTouchingTop(u16, u16, u16, u16);
bool isTouchingBottom(u16, u16, u16, u16);

#endif