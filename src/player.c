#include "player.h"
#include "game.h"
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

s8 isTouchingCoin(Player *player, u16 x, u16 y, u16 w, u16 h)
{
    BoxCollider box1 = {x, y, w, h};
    BoxCollider box2 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH, PADDLE_WIDTH, PADDLE_HEIGTH};
    if (isColliding(&box1, &box2))
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

s8 isTouchingPaddle(Player *player, u16 x, u16 y, u16 w, u16 h)
{
    u16 h_prime = (PADDLE_HEIGTH - 2 * PADDLE_EXTREME_HEIGTH) / 2;
    // medio arriba
    BoxCollider box1 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH + PADDLE_EXTREME_HEIGTH + 1, PADDLE_WIDTH, h_prime};
    // ball
    BoxCollider box2 = {x, y, w, h};
    // medio abajo
    BoxCollider box3 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH + (PADDLE_HEIGTH / 2) + 1, PADDLE_WIDTH, h_prime};
    // bottom
    BoxCollider box4 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH + PADDLE_HEIGTH - PADDLE_EXTREME_HEIGTH, PADDLE_WIDTH, PADDLE_EXTREME_HEIGTH};
    // top
    BoxCollider box6 = {player->x + PADDEL_OFFSET_WIDTH, player->y + PADDLE_OFFSET_HEIGTH, PADDLE_EXTREME_WIDTH, PADDLE_EXTREME_HEIGTH};

    if (isColliding(&box1, &box2))
    {
        return -1;
    }
    else
    {
        if (isColliding(&box3, &box2))
        {
            return 1;
        }
        else
        {
            if (isColliding(&box4, &box2))
            {
                return 2;
            }
            else
            {
                if (isColliding(&box6, &box2))
                {
                    return 4;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}

void drawPlayer(Player *player)
{
    SPR_setPosition(player->sprite, player->x, player->y);
    SPR_setFrame(player->marc, player->score);
}