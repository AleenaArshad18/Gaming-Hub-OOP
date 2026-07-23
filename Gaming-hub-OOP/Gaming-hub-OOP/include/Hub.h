#ifndef HUB_H
#define HUB_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

enum GameState
{
    HUB_SCREEN,
    TIC_TAC_TOE_SCREEN,
    PONG_SCREEN,
    BRICK_BREAKER_SCREEN,
    LEADER_BOARD_SCREEN,

    TTT_NAME_SCREEN,
    TTT_WIN_SCREEN,
    PONG_NAME_SCREEN,
    BRICK_NAME_SCREEN
};

class Hub
{
private:

    Font font;
    Text title;

    RectangleShape ticTacToeButton;
    Text ticTacToeText;

    RectangleShape pongButton;
    Text pongText;

    RectangleShape brickButton;
    Text brickText;

    RectangleShape leaderboardButton;
    Text leaderboardText;

    SoundBuffer buttonClickSoundBuffer; 
    Sound buttonClickSound;              

public:

    Hub();

    void handleEvent(RenderWindow& window, Event& event, GameState& screen);
    void checkHover(RenderWindow& window);
    void draw(RenderWindow& window);
};

#endif