#pragma once
#include "leaderboard.h"
#include "Hub.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace sf;
using namespace std;

class PingPong
{
private:
    float ballSpeedX;
    float ballSpeedY;
    float paddleSpeed;

    int leftLives;
    int rightLives;

    Leaderboard leaderboard;

    RectangleShape leftPaddle;
    RectangleShape rightPaddle;

    Texture ballTexture;
    Sprite  ball;
    float       ballRadius;

    Font font;
    Text scoreText;    
    Text gameOverText;   

    string leftPlayerName;
    string rightPlayerName;

    SoundBuffer paddleHitSoundBuffer;
    Sound paddleHitSound;

    SoundBuffer lifeLostSoundBuffer;   
    Sound lifeLostSound;             

    SoundBuffer winSoundBuffer;     
    Sound winSound;                    

    bool winnerSaved;
    
    Text leftNameText;    
    Text rightNameText;  

    bool showWinOverlay;            
    RectangleShape dimOverlay; 
    RectangleShape winBox;     
    Text winText;            

    RectangleShape playAgainButton;
    Text playAgainText;

    RectangleShape mainMenuButton;
    Text mainMenuText;

public:

    PingPong();

    void setPlayerNames(const string& leftName, const string& rightName);

    void handleInput();
    void update(Leaderboard& leaderboard);
    void draw(RenderWindow& window);
    void resetGame();
    void resetBall();

    void handleEvent(RenderWindow& window, Event& event, GameState& screen); 
    bool isShowingWinOverlay() const { return showWinOverlay; }
};
