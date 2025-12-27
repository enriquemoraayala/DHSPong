#include "player.h"
#include "physics.h"

void updatePlayer(Player *player)
{
    switch (player->input)
    {
    case UP:
        if (!isTouchingTop(player->x + 10, player->y + 2, PADDLE_WIDTH, PADDLE_HEIGTH))
        {
            player->y -= PLAYER_SPEED;
        }
        break;
    case DOWN:
        if (!isTouchingBottom(player->x + 10, player->y + 4, PADDLE_WIDTH, PADDLE_HEIGTH))
        {
            player->y += PLAYER_SPEED;
        }
        break;
    default:
        break;
    }
}

s8 isTouchingPaddle(Player *player, u16 x, u16 y, u16 w, u16 h)
{
    u16 halfpaddleheigth = PADDLE_HEIGTH / 2;
    BoxCollider box1 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH, PADDLE_WIDTH, halfpaddleheigth};
    BoxCollider box2 = {x, y, w, h};
    BoxCollider box3 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH + halfpaddleheigth + 1, PADDLE_WIDTH, halfpaddleheigth};
    // debajo - delante
    BoxCollider box4 = {player->x + PADDEL_OFFSET_WIDTH + PADDLE_EXTREME_WIDTH + 1, player->y + PADDLE_OFFSET_HEIGTH + PADDLE_HEIGTH - PADDLE_EXTREME_HEIGTH, PADDLE_EXTREME_WIDTH + 1, PADDLE_EXTREME_HEIGTH};
    // debajo - detras
    // BoxCollider box5 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH + PADDLE_HEIGTH - PADDLE_EXTREME_HEIGTH, PADDLE_EXTREME_WIDTH, PADDLE_EXTREME_HEIGTH};

    
    
    if (isColliding(&box1, &box2))
    {
        return -1;
    }
    else
    {
        if (isColliding(&box3, &box2))
        {
            KLog("Colliding box3,box2");
            KLog_S1("Box- x: ",player->x + PADDEL_OFFSET_WIDTH);
            KLog_S1("Box- y: ",player->y + PADDLE_OFFSET_HEIGTH + halfpaddleheigth + 1);
            KLog_S1("Box- w:", PADDLE_WIDTH);
            KLog_S1("Box- h:", halfpaddleheigth);
            KLog_S1("Ball - x: ",x);
            KLog_S1("Ball - y: ", y);
            KLog_S1("Ball - w:", w);
            KLog_S1("Ball - h:", h);
            return 1;
        }
        else
        {
            if (isColliding(&box4, &box2))
            {
                KLog("Colliding box4,box2");
                KLog_S1("Box- x: ",player->x + PADDEL_OFFSET_WIDTH + PADDLE_EXTREME_WIDTH + 1);
                KLog_S1("Box- y: ", player->y + PADDLE_OFFSET_HEIGTH + PADDLE_HEIGTH - PADDLE_EXTREME_HEIGTH);
                KLog_S1("Box- w:", PADDLE_EXTREME_WIDTH + 1);
                KLog_S1("Box- h:", PADDLE_EXTREME_HEIGTH);
                KLog_S1("Ball - x: ",x);
                KLog_S1("Ball - y: ", y);
                KLog_S1("Ball - w:", w);
                KLog_S1("Ball - h:", h);
                return 2;
            }
            else
            {
                return 0;
            }
        }
    }
}

void drawPlayer(Player *player)
{
    SPR_setPosition(player->sprite, player->x, player->y);
    SPR_setFrame(player->marc, player->score);
}