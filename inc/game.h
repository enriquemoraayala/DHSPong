#ifndef _H_GAME
#define _H_GAME

    #include <genesis.h>
    #include "player.h"

    typedef enum state
    {
        INIT_MENU,
        MENU,
        INIT_GAME,
        LOOP_GAME,
        GAME_OVER,
        PAUSE

    } Status;

    typedef struct
    {
        Sprite *sprite;
        Sprite * impactSpr;
        s16 x;
        s16 y;
        s16 dx;
        s16 dy;
        bool launched;
        bool impact;
    } Ball;

    typedef struct
    {
        Player player1;
        Player player2;
        Ball ball;
        Status state;
        u8 lastScored;
        bool singlePlayer;
    } Game;

    struct{
        Sprite * menuSel1;
        Sprite * menuSel2;
        bool twoPlayers;
    } menuStruct;

    extern Game game;

    void initMenu(void);

    void drawInitMenu(void);

    void updateMenu(void);

    void drawMenu(void);

    void initGame();

    Input checkInput(u16);

    Input iaInput();

    void updateGame();

    void updateGameOver();

    void drawGameOver();

    void drawGame();

    void drawInitGame();

    void updateBall();

    void deInitGame();

    void drawBall();

#endif
