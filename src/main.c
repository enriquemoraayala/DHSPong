/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "game.h"
#include "player.h"

void init();

void checkInputs();

void update();

void draw();

int main()
{

    init();
    while (1)
    {
        checkInputs();
        update();
        draw();
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}

void init()
{
    VDP_setScreenWidth320();
    JOY_init();
    SPR_init();
    game.state = INIT_MENU;
    game.singlePlayer = TRUE;
}

void checkInputs()
{
    game.player1.input = checkInput(JOY_1);
    if (!game.singlePlayer)
    {
        game.player2.input = checkInput(JOY_2);
    }
    else
    {
        game.player2.input = iaInput();
    }
}

void update()
{
    switch (game.state)
    {
    case INIT_MENU:
        initMenu();
        break;
    case MENU:
        updateMenu();
        break;
    case INIT_GAME:
        initGame();
        break;
    case LOOP_GAME:
        updateGame();
        break;
    case GAME_OVER:
        updateGameOver();
        break;
    default:
        break;
    }
}

void draw()
{
    switch (game.state)
    {
    case INIT_MENU:
        drawInitMenu();
        break;
    case MENU:
        drawMenu();
        break;
    case INIT_GAME:
        drawInitGame();
        game.state=LOOP_GAME;
        break;
    case LOOP_GAME:
        drawGame();
        break;
    case GAME_OVER:
        drawGameOver();
    default:
        break;
    }
}



