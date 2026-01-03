#include "game.h"
#include "physics.h"
#include "globals.h"
#include "kdebug.h"
#include "sprt.h"
#include "sound.h"

void paddelTouched(s8 paddelTouch);
void restartGame();
void deInitImpact(Sprite *);

void updateBall()
{
    if (!game.ball.launched)
    {
        if (game.player1.input == A)
        {
            if (game.lastScored == 1)
            {
                game.ball.dx = -BALL_SPEED;
                game.ball.dy = BALL_SPEED;
            }
            else
            {
                game.ball.dx = BALL_SPEED;
                game.ball.dy = -BALL_SPEED;
            }
            game.ball.launched = TRUE;
        }
    }
    else
    {
        if (isTouchingTop(game.ball.x + 8, game.ball.y + 8, 13, 13))
        {
            if (game.ball.dy < -BALL_SPEED)
            {
                game.ball.dy = BALL_MAX_SPEED;
            }
            else
            {
                game.ball.dy = BALL_SPEED;
            }
            game.ball.impact = TRUE;
            game.ball.bounced = TRUE;
            XGM2_playPCM(bounce, sizeof(bounce), SOUND_PCM_CH_AUTO);
        }
        if (isTouchingBottom(game.ball.x + 8, game.ball.y + 8, 13, 13))
        {
            XGM2_playPCM(bounce, sizeof(bounce), SOUND_PCM_CH_AUTO);
            if (game.ball.dy > BALL_SPEED)
            {
                game.ball.dy = -BALL_MAX_SPEED;
            }
            else
            {
                game.ball.dy = -BALL_SPEED;
            }
            game.ball.impact = TRUE;
            game.ball.bounced = TRUE;
        }

        if (isTouchingLeftEdge(game.ball.x + 8, game.ball.y + 8, 13, 13))
        {
            game.player2.score++;
            game.lastScored = 2;
            if (game.player2.score > MAX_GOALS)
            {
                deInitGame();
                game.state = GAME_OVER;
            }
            else
            {
                game.ball.goalhit = TRUE;
                restartGame();
            }
        }

        if (isTouchingRightEdge(game.ball.x + 8, game.ball.y + 8, 13, 13))
        {
            game.player1.score++;
            game.lastScored = 1;
            if (game.player1.score > 9)
            {
                deInitGame();
                game.state = GAME_OVER;
            }
            else
            {
                game.ball.goalhit = TRUE;
                restartGame();
            }
        }
        s8 touchingpaddel1 = isTouchingPaddle(&game.player1, game.ball.x + BALL_OFFSET, game.ball.y + BALL_OFFSET, BALL_DIAMETRE, BALL_DIAMETRE);
        if (touchingpaddel1 != 0)
        {
            paddelTouched(touchingpaddel1);
            KLog_S1("Toca el paddle 1: ", touchingpaddel1);
            KLog_S1("dx: ", game.ball.dx);
            KLog_S1("dy: ", game.ball.dy);
        }
        s8 touchingpaddel2 = isTouchingPaddle(&game.player2, game.ball.x + BALL_OFFSET, game.ball.y + BALL_OFFSET, BALL_DIAMETRE, BALL_DIAMETRE);
        paddelTouched(touchingpaddel2);

        game.ball.x += game.ball.dx;
        game.ball.y += game.ball.dy;
    }
}

void paddelTouched(s8 paddelTouch)
{
    // value 0 = FALSE
    // value != o -> hemos tocado algo
    if (paddelTouch)
    {
        XGM2_playPCM(playerhit, sizeof(playerhit), SOUND_PCM_CH_AUTO);   
        game.ball.impact = TRUE;
        game.ball.paddlehit = TRUE;
        switch (paddelTouch)
        {
        case -1:
            game.ball.dx = CHANGE_SIGN(game.ball.dx);
            game.ball.dy = -BALL_SPEED;
            break;
        case 1:
            game.ball.dx = CHANGE_SIGN(game.ball.dx);
            game.ball.dy = BALL_SPEED;
            break;
        case 2:
            // si la toco la bola con la parte inferior del paddle, sale más rápido
            game.ball.dx = CHANGE_SIGN(game.ball.dx);
            game.ball.dy = BALL_MAX_SPEED;
            break;
        case 3:
            game.ball.x = BALL_INITIAL_X;
            game.ball.y = BALL_INITIAL_Y;
            break;
        case 4:
            // si la toco la bola con la parte superior del paddle, sale más rápido
            game.ball.dx = CHANGE_SIGN(game.ball.dx);
            game.ball.dy = -BALL_MAX_SPEED;
            break;
        }
    }
}

void restartGame()
{
    game.player1.x = PLAYER1_INITIAL_X;
    game.player1.y = PLAYER_INITIAL_Y;
    game.player2.x = PLAYER2_INITIAL_X;
    game.player2.y = PLAYER_INITIAL_Y;
    game.ball.dx = 0;
    game.ball.dy = 0;
    game.ball.x = BALL_INITIAL_X;
    game.ball.y = BALL_INITIAL_Y;
    game.ball.launched = FALSE;
    game.lastScored = 1;
    game.ball.bounced = FALSE;
    game.ball.goalhit = FALSE;
    game.ball.paddlehit = FALSE;
}

void drawBall()
{
    SPR_setPosition(game.ball.sprite, game.ball.x, game.ball.y);
    if (game.ball.impact)
    {
        game.ball.impactSpr = SPR_addSprite(&hit, game.ball.x + 4, game.ball.y + 4, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
        SPR_setFrameChangeCallback(game.ball.impactSpr, deInitImpact);
        game.ball.impact = FALSE;
    }
    if (game.ball.bounced)
    {
       // XGM2_playPCM(bounce, sizeof(bounce), SOUND_PCM_CH_AUTO);
        game.ball.bounced = FALSE;
    }
    if (game.ball.goalhit)
    {
        XGM2_playPCM(goal, 6912, SOUND_PCM_CH_AUTO);
        game.ball.goalhit = FALSE;
    }
    if (game.ball.paddlehit)
    {
        // XGM2_playPCM(playerhit, 6912, SOUND_PCM_CH_AUTO);
        game.ball.paddlehit = FALSE;
    }
}

void deInitImpact(Sprite *sprite)
{
    if (sprite->frameInd == 3)
    {
        SPR_releaseSprite(sprite);
    }
}