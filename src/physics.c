#include <genesis.h>
#include "physics.h"

bool isColliding(BoxCollider *box1, BoxCollider *box2)
{
    u16 box1_x1 = box1->x;
    u16 box1_y1 = box1->y;
    u16 box1_x2 = box1->x + box1->w;
    u16 box1_y2 = box1->y + box1->h;

    u16 box2_x1 = box2->x;
    u16 box2_y1 = box2->y;
    u16 box2_x2 = box2->x + box2->w;
    u16 box2_y2 = box2->y + box2->h;

    if ((box1_x1 <= box2_x2) && (box1_x2 >= box2_x1) && (box1_y1 <= box2_y2) && (box1_y2 >= box2_y1))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool isTouchingTop(u16 x, u16 y, u16 w, u16 h)
{
    BoxCollider box1 = {x, y, w, h};
    BoxCollider box2 = {TOP_EDGE, TOP_EDGE_Y, EDGE_WIDTH, EDGE_HEIGHT};
    return isColliding(&box1, &box2);
}

bool isTouchingBottom(u16 x, u16 y, u16 w, u16 h)
{
    BoxCollider box1 = {x, y, w, h};
    BoxCollider box2 = {BOTTOM_EDGE, BOTTOM_EDGE_Y, EDGE_WIDTH, EDGE_HEIGHT};
    return isColliding(&box1, &box2);
}

bool isTouchingLeftEdge(u16 x, u16 y, u16 w, u16 h){
    BoxCollider box1 = {x, y, w, h};
    BoxCollider box2 = {TOP_EDGE, TOP_EDGE, LATERAL_EDGE_WIDTH, LATERAL_EDGE_HEIGHT};
    return isColliding(&box1, &box2);
}

bool isTouchingRightEdge(u16 x, u16 y, u16 w, u16 h){
    BoxCollider box1 = {x, y, w, h};
    BoxCollider box2 = {LATERAL_EDGE, 0, LATERAL_EDGE_WIDTH, LATERAL_EDGE_HEIGHT};
    return isColliding(&box1, &box2);
}