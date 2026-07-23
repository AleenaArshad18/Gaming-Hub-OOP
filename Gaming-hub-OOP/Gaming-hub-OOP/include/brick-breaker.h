#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "leaderboard.h"
#include "Hub.h"        
#include <string>
using namespace sf;
using namespace std;

class BrickBreaker
{
private:

    RectangleShape paddle;
    Texture ballTexture;
    Sprite ball;
    float ballRadius;

    float ballSpeedX;
    float ballSpeedY;
    float paddleSpeed;

    static const int ROWS = 5;
    static const int COLS = 10;

    RectangleShape bricks[ROWS][COLS];
    bool brickVisible[ROWS][COLS];

    Font font;
    Text scoreText;

    int score;
    Leaderboard leaderboard;

    // Lives system
    int lives;
    static const int MAX_LIVES = 3;
    Texture heartTexture;
    Sprite  hearts[MAX_LIVES];

    string playerName;

    bool gameEnded;                  
    RectangleShape dimOverlay;  
    RectangleShape endBox;       
    Text endTitleText;         
    Text endScoreText;       

    RectangleShape playAgainButton;
    Text playAgainText;

    RectangleShape mainMenuButton;
    Text mainMenuText;

    SoundBuffer brickHitSoundBuffer;   
    Sound brickHitSound;             

    SoundBuffer paddleHitSoundBuffer;  
    Sound paddleHitSound;             

    SoundBuffer lifeLostSoundBuffer;   
    Sound lifeLostSound;         

public:

    BrickBreaker();

    void setPlayerName(const string& name);   

    void handleInput();
    void update(Leaderboard& leaderboard);
    void draw(RenderWindow& window);
    void resetGame();

    void handleEvent(RenderWindow& window, Event& event, GameState& screen);  
    bool isGameEnded() const { return gameEnded; }  

};
