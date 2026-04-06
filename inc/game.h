#ifndef _H_GAME
    #define _H_GAME

    #include <genesis.h>
    #include "player.h"
    #include "physics.h"

    typedef enum state
    {
        INIT_LOGO,
        LOGO,
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
        bool bounced;
        bool goalhit;
        bool paddlehit;
    } Ball;

    typedef struct{
        Sprite *coinSpr;
        s16 x;
        s16 y;
        s16 dx;
        s16 dy;
        bool active;
    } Coin;

    typedef struct
    {
        Player player1;
        Player player2;
        Ball ball;
        Coin coins[MAX_COINS];
        Status state;
        u8 lastScored;
        bool singlePlayer;
    } Game;

    typedef struct{
        Sprite * menuSel1;
        Sprite * menuSel2;
        bool twoPlayers;
    } MenuStruct;

    extern MenuStruct menuStruct;
    extern Game game;

    void initLogo(void);

    void drawInitLogo(void);

    void updateLogo(void);

    void drawLogo(void);

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

    void drawInitCoins(void);

    void updateBall();

    void activateCoins(Player *);

    void deInitGame();

    void drawBall();

    void initCoin(void);

    void resetCoins(void);

    void updateCoins(void);

    void drawCoins(void);

    void hideCoin(Coin *);

    s8 activateNextCoin(void);

#endif
