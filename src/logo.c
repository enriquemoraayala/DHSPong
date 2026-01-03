#include <genesis.h>
#include "game.h"
#include "gfx.h"


u16 frameCounter;

void initLogo(void){
    frameCounter = 0;
}

void drawInitLogo(void){
    u16 index = TILE_USER_INDEX;
    SYS_disableInts();
    PAL_setPalette(PAL0, logo.palette->data, DMA);
    VDP_drawImageEx(BG_A, &logo, TILE_ATTR_FULL(PAL0,FALSE, FALSE, FALSE, index), 0, 0, FALSE, DMA);
    SYS_enableInts();
    game.state = LOGO;
}

void updateLogo(void){
    frameCounter++;
}

void drawLogo(void){
    if(frameCounter > 240){
        PAL_fadeOut(0,63,30,FALSE);
        game.state = INIT_MENU;
    }
}