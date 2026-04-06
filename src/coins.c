#include <genesis.h>
#include "physics.h"
#include "game.h"
#include "sprt.h"
#include "kdebug.h"

void resetCoins(void)
{
    for (u16 i = 0; i < MAX_COINS; i++)
    {
        game.coins[i].x = 0;
        game.coins[i].y = 0;
        game.coins[i].dx = 0;
        game.coins[i].dy = 0;
        game.coins[i].active = FALSE;

        if (game.coins[i].coinSpr != NULL)
        {
            SPR_setVisibility(game.coins[i].coinSpr, HIDDEN);
            SPR_setPosition(game.coins[i].coinSpr, 0, 0);
        }
    }
}

void drawInitCoin(void)
{
    PAL_setPalette(PAL2, coin.palette->data, DMA);
    for (u16 i = 0; i < MAX_COINS; i++)
    {
        game.coins[i].coinSpr = SPR_addSprite(&coin, 0, 0, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
        SPR_setAnim(game.coins[i].coinSpr, 0);
    }
    resetCoins();
}

s8 activateNextCoin(void)
{
    for (u8 i = 0; i < MAX_COINS; i++)
    {
        if (game.coins[i].active == FALSE)
        {
            game.coins[i].active = TRUE;
            game.coins[i].x = INIT_COIN_X;
            game.coins[i].y = INIT_COIN_Y;
            SPR_setVisibility(game.coins[i].coinSpr, VISIBLE);
            return i;
        }
    }
    return -1;
}

void hideCoin(Coin *coin)
{
    coin->active = FALSE;
    SPR_setVisibility(coin->coinSpr, HIDDEN);
}


void updateCoins(void)
{
    for (u8 i = 0; i < game.player1.numActiveCoins; i++)
    {
        game.coins[game.player1.playerCoins[i]].x -= COIN_SPEED;
        s8 coinIndex = isTouchingCoin(&game.player1, game.coins[game.player1.playerCoins[i]].x, game.coins[game.player1.playerCoins[i]].y, 16, 16);
        if (coinIndex >= 0)
        {
            hideCoin(&game.coins[game.player1.playerCoins[i]]);
        }
    }
    for (u8 i = 0; i < game.player2.numActiveCoins; i++)
    {
        game.coins[game.player2.playerCoins[i]].x += COIN_SPEED;
        s8 coinIndex = isTouchingCoin(&game.player2, game.coins[game.player2.playerCoins[i]].x, game.coins[game.player2.playerCoins[i]].y, 16, 16);
        if (coinIndex >= 0)
        {
            hideCoin(&game.coins[game.player2.playerCoins[i]]);
        }
    }
}

void drawCoins(void)
{
    for (u16 i = 0; i < MAX_COINS; i++)
    {
        if (game.coins[i].active)
        {
            SPR_setPosition(game.coins[i].coinSpr, game.coins[i].x, game.coins[i].y);
        }
    }
}
