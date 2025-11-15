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
        if (!isTouchingBottom(player->x + 10, player->y + 2, PADDLE_WIDTH, PADDLE_HEIGTH))
        {
            player->y += PLAYER_SPEED;
        }
        break;
    default:
        break;
    }
    
}

void drawPlayer(Player *player)
{
    SPR_setPosition(player->sprite, player->x, player->y);
}