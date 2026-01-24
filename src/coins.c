#include <genesis.h>
#include "physics.h"
#include "game.h"
#include "sprt.h"

void initCoin(void){
    for (u16 i = 0; i < MAX_COINS; i++)
    {
        coins[i].coinSpr = SPR_addSprite(&coin, 0, 0, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
        coins[i].active = FALSE;
        SPR_setVisibility(coins[i].coinSpr, HIDDEN);
    }

}

void hideCoin(Coin *coin){
    coin->active = FALSE;
    SPR_setVisibility(coin->coinSpr, HIDDEN);
}

void drawCoin(void){
  for (u16 i = 0; i < MAX_COINS; i++)
    {
        
        coins[i].active = FALSE;
        SPR_setVisibility(coins[i].coinSpr, HIDDEN);
    }
}


