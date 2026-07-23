#include "pong.h"
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

PingPong::PingPong()
{
    font.loadFromFile("PixelPurl.ttf");

    leftPaddle.setSize(Vector2f(20, 100));
    leftPaddle.setFillColor(Color(27, 62, 107));
    leftPaddle.setPosition(50, 300);

    rightPaddle.setSize(Vector2f(20, 100));
    rightPaddle.setFillColor(Color(27, 62, 107));
    rightPaddle.setPosition(930, 300);

    paddleSpeed = 1.5;

    if (!ballTexture.loadFromFile("ball-sprite-pingpong-removebg-preview.png"))
        cout << "Ball sprite not loaded\n";

    if (!paddleHitSoundBuffer.loadFromFile("mixkit-player-jumping-in-a-video-game-2043.wav"))  
        cout << "Paddle hit sound not loaded\n";                                   

    if (!lifeLostSoundBuffer.loadFromFile("floraphonic-classic-game-action-negative-8-224414.wav"))  
        cout << "Life lost sound not loaded\n";                                               
    lifeLostSound.setBuffer(lifeLostSoundBuffer);                                                    

    if (!winSoundBuffer.loadFromFile("mixkit-completion-of-a-level-2063.wav"))  
        cout << "Win sound not loaded\n";                              
    winSound.setBuffer(winSoundBuffer);

    paddleHitSound.setBuffer(paddleHitSoundBuffer);

    ball.setTexture(ballTexture);
    ballRadius = 35.f;
    float diameter = ballRadius * 2.f;
    Vector2u texSize = ballTexture.getSize();
    ball.setScale(diameter / texSize.x, diameter / texSize.y);
    ball.setOrigin(texSize.x / 2.f, texSize.y / 2.f);

    ballSpeedX = 0.005;
    ballSpeedY = 0.005;

    scoreText.setFont(font);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setOutlineColor(Color::Black);
    scoreText.setOutlineThickness(2);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(270, 20);

    gameOverText.setFont(font);
    gameOverText.setFillColor(Color(255, 0, 127));
    gameOverText.setOutlineColor(Color(102, 0, 51));
    gameOverText.setOutlineThickness(2);
    gameOverText.setCharacterSize(40);
    gameOverText.setPosition(350, 320);

    leftPlayerName = "Left Player";
    rightPlayerName = "Right Player";
    winnerSaved = false;

    leftNameText.setFont(font);
    leftNameText.setCharacterSize(34);
    leftNameText.setFillColor(Color(178, 102, 255));   
    leftNameText.setPosition(20, 15);                    
    leftNameText.setOutlineThickness(2);

    rightNameText.setFont(font);
    rightNameText.setCharacterSize(34);
    rightNameText.setFillColor(Color(178, 102, 255));  
    rightNameText.setOutlineThickness(2);

    dimOverlay.setSize(Vector2f(1000, 700));
    dimOverlay.setPosition(0, 0);
    dimOverlay.setFillColor(Color(0, 0, 0, 160));  

    winBox.setSize(Vector2f(500, 320));
    winBox.setPosition(250, 190);
    winBox.setFillColor(Color(20, 20, 40, 240)); 
    winBox.setOutlineThickness(3);
    winBox.setOutlineColor(Color(178, 102, 255));

    winText.setFont(font);
    winText.setCharacterSize(40);
    winText.setFillColor(Color(178, 102, 255));
    winText.setPosition(280, 230);

    playAgainButton.setSize(Vector2f(200, 55));
    playAgainButton.setPosition(280, 360);
    playAgainButton.setFillColor(Color(80, 150, 200));

    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(Color::White);
    playAgainText.setPosition(300, 375);

    mainMenuButton.setSize(Vector2f(200, 55));
    mainMenuButton.setPosition(520, 360);
    mainMenuButton.setFillColor(Color(200, 80, 80));

    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(24);
    mainMenuText.setFillColor(Color::White);
    mainMenuText.setPosition(540, 375);

    showWinOverlay = false;  

    resetGame();
}


void PingPong::setPlayerNames(const string& leftName, const string& rightName)
{
    leftPlayerName = leftName;
    rightPlayerName = rightName;

    leftNameText.setString(leftPlayerName);

    rightNameText.setString(rightPlayerName);
    float textWidth = rightNameText.getLocalBounds().width;
    rightNameText.setPosition(1000.f - textWidth - 20.f, 15.f);
}


void PingPong::resetGame()
{
    leftLives = 5;
    rightLives = 5;
    winnerSaved = false;
    showWinOverlay = false; 

    leftPaddle.setPosition(50, 300);
    rightPaddle.setPosition(930, 300);

    gameOverText.setString("");

    resetBall();
}

void PingPong::resetBall()
{
    ball.setPosition(500, 350);
    ballSpeedX = 0.25;
    ballSpeedY = 0.25;
}

void PingPong::handleInput()
{
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        if (leftPaddle.getPosition().y > 0)
            leftPaddle.move(0, -paddleSpeed);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if (leftPaddle.getPosition().y < 600)
            leftPaddle.move(0, paddleSpeed);
    }
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        if (rightPaddle.getPosition().y > 0)
            rightPaddle.move(0, -paddleSpeed);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        if (rightPaddle.getPosition().y < 600)
            rightPaddle.move(0, paddleSpeed);
    }
}

void PingPong::update(Leaderboard& leaderboard)
{
    if (leftLives == 0 || rightLives == 0)
        return;

    ball.move(ballSpeedX, ballSpeedY);

    if (ball.getPosition().y <= 0 || ball.getPosition().y >= 680)
        ballSpeedY = -ballSpeedY;

    if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) && ballSpeedX < 0) {
        ballSpeedX = -ballSpeedX;
        paddleHitSound.play();
    }

    if (ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()) && ballSpeedX > 0) {
        ballSpeedX = -ballSpeedX;
        paddleHitSound.play();
    }

    if (ball.getPosition().x < 0)
    {
        leftLives--;
        lifeLostSound.play(); 
        resetBall();
    }

    if (ball.getPosition().x > 1000)
    {
        rightLives--;
        lifeLostSound.play();  
        resetBall();
    }

    leftNameText.setString(leftPlayerName + "  Lives: " + to_string(leftLives));

    rightNameText.setString(rightPlayerName + "  Lives: " + to_string(rightLives));
    float textWidth = rightNameText.getLocalBounds().width;
    rightNameText.setPosition(1000.f - textWidth - 20.f, 15.f);

    if (leftLives == 0 && !winnerSaved)
    {
        winText.setString(rightPlayerName + " Wins!");
        leaderboard.saveScore(rightPlayerName, "Pong", 1);
        winnerSaved = true;
        showWinOverlay = true;
        winSound.play();  
    }

    if (rightLives == 0 && !winnerSaved)
    {
        winText.setString(leftPlayerName + " Wins!");
        leaderboard.saveScore(leftPlayerName, "Pong", 1);
        winnerSaved = true;
        showWinOverlay = true;
        winSound.play(); 
    }
}


void PingPong::draw(RenderWindow& window)
{

    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
    window.draw(leftNameText);   
    window.draw(rightNameText);

    if (showWinOverlay)
    {
        window.draw(dimOverlay);   
        window.draw(winBox);
        window.draw(winText);
        window.draw(playAgainButton);
        window.draw(playAgainText);
        window.draw(mainMenuButton);
        window.draw(mainMenuText);
    }
}

void PingPong::handleEvent(RenderWindow& window, Event& event, GameState& screen)
{
    if (!showWinOverlay)
        return;

    if (event.type == Event::MouseButtonPressed)
    {
        Vector2i mouse = Mouse::getPosition(window);

        if (playAgainButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            resetGame();       
            screen = PONG_NAME_SCREEN;
        }

        if (mainMenuButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            resetGame();
            screen = HUB_SCREEN;
        }
    }
}