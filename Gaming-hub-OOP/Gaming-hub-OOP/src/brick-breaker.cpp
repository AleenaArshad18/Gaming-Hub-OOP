#include "brick-breaker.h"
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

BrickBreaker::BrickBreaker()
{
    font.loadFromFile("PixelPurl.ttf");

    paddle.setSize(Vector2f(120, 20));
    paddle.setFillColor(Color(19, 64, 107));
    paddle.setPosition(440, 650);

    paddleSpeed = 1.2;

    if (!ballTexture.loadFromFile("blue-ball-brickbreaker2-removebg-preview.png"))
        cout << "Ball sprite not loaded\n";


    if (!brickHitSoundBuffer.loadFromFile("mixkit-retro-arcade-casino-notification-211.wav"))  
        cout << "Brick hit sound not loaded\n";                                           
    brickHitSound.setBuffer(brickHitSoundBuffer);                                               

    if (!paddleHitSoundBuffer.loadFromFile("mixkit-player-jumping-in-a-video-game-2043.wav"))  
        cout << "Paddle hit sound not loaded\n";                                         
    paddleHitSound.setBuffer(paddleHitSoundBuffer);                                              

    if (!lifeLostSoundBuffer.loadFromFile("floraphonic-classic-game-action-negative-8-224414.wav")) 
        cout << "Life lost sound not loaded\n";                                                
    lifeLostSound.setBuffer(lifeLostSoundBuffer);


    ball.setTexture(ballTexture);

    ballRadius = 22.f;
    float diameter = ballRadius * 2.f;
    Vector2u texSize = ballTexture.getSize();
    ball.setScale(diameter / texSize.x, diameter / texSize.y);
    ball.setOrigin(texSize.x / 2.f, texSize.y / 2.f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color(173, 200, 240));
    scoreText.setOutlineColor(Color::Black);
    scoreText.setOutlineThickness(2);
    scoreText.setPosition(20, 10);

    if (!heartTexture.loadFromFile("dark_blue_heart_pixel_art-removebg-preview.png"))
        cout << "Heart sprite not loaded\n";

    for (int i = 0; i < MAX_LIVES; i++)
    {
        hearts[i].setTexture(heartTexture);

        Vector2u hTexSize = heartTexture.getSize();  
        float desiredSize = 55.f;
        hearts[i].setScale(desiredSize / hTexSize.x, desiredSize / hTexSize.y);

        hearts[i].setPosition(800 + i * 45, 10);
    }

    playerName = "Player";  
    
    dimOverlay.setSize(Vector2f(1000, 700));
    dimOverlay.setPosition(0, 0);
    dimOverlay.setFillColor(Color(0, 0, 0, 160));   

    endBox.setSize(Vector2f(500, 340));
    endBox.setPosition(250, 180);
    endBox.setFillColor(Color(20, 20, 40, 240));
    endBox.setOutlineThickness(3);
    endBox.setOutlineColor(Color(178, 102, 255));

    endTitleText.setFont(font);
    endTitleText.setCharacterSize(38);
    endTitleText.setFillColor(Color(178, 102, 255));
    endTitleText.setPosition(280, 215);

    endScoreText.setFont(font);
    endScoreText.setCharacterSize(30);
    endScoreText.setFillColor(Color::White);
    endScoreText.setPosition(280, 280);

    playAgainButton.setSize(Vector2f(200, 55));
    playAgainButton.setPosition(280, 380);
    playAgainButton.setFillColor(Color(80, 150, 200));

    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(Color::White);
    playAgainText.setPosition(300, 395);

    mainMenuButton.setSize(Vector2f(200, 55));
    mainMenuButton.setPosition(520, 380);
    mainMenuButton.setFillColor(Color(200, 80, 80));

    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(24);
    mainMenuText.setFillColor(Color::White);
    mainMenuText.setPosition(540, 395);

    gameEnded = false;   

    resetGame();
}

void BrickBreaker::setPlayerName(const string& name)
{
    playerName = name;
}

void BrickBreaker::resetGame()
{
    score = 0;
    lives = MAX_LIVES;
    gameEnded = false;  

    ball.setPosition(500, 500);
    ballSpeedX = 0.25;
    ballSpeedY = -0.25;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            bricks[i][j].setSize(Vector2f(80, 25));

            float t = (float)i / (ROWS - 1);
            int startR = 10, startG = 20, startB = 80;
            int endR = 180, endG = 220, endB = 255;
            int r = startR + (int)((endR - startR) * t);
            int g = startG + (int)((endG - startG) * t);
            int b = startB + (int)((endB - startB) * t);
            bricks[i][j].setFillColor(Color(r, g, b));

            bricks[i][j].setPosition(60 + j * 90, 60 + i * 40);
            brickVisible[i][j] = true;
        }
    }
}

void BrickBreaker::handleInput()
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        if (paddle.getPosition().x > 0)
            paddle.move(-paddleSpeed, 0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        if (paddle.getPosition().x < 880)
            paddle.move(paddleSpeed, 0);
    }
}

void BrickBreaker::update(Leaderboard& leaderboard)
{
    if (gameEnded)
        return;

    ball.move(ballSpeedX, ballSpeedY);

    if (ball.getPosition().x <= 0 || ball.getPosition().x >= 980)
        ballSpeedX = -ballSpeedX;

    if (ball.getPosition().y <= 0)
        ballSpeedY = -ballSpeedY;

    if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
    {
        ballSpeedY = -ballSpeedY;
        paddleHitSound.play(); 
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (brickVisible[i][j])
            {
                if (ball.getGlobalBounds().intersects(bricks[i][j].getGlobalBounds()))
                {
                    brickVisible[i][j] = false;
                    ballSpeedY = -ballSpeedY;
                    score += 10;
                    brickHitSound.play();  
                }
            }
        }
    }

    scoreText.setString("Score: " + to_string(score));

    if (ball.getPosition().y > 700)
    {
        lives--;
        lifeLostSound.play(); 

        if (lives <= 0)
        {
            leaderboard.saveScore(playerName, "BrickBreaker", score);

            endTitleText.setString(playerName);
            endScoreText.setString("Final Score: " + to_string(score));

            gameEnded = true;
        }
        else
        {
            ball.setPosition(500, 500);
            ballSpeedX = 0.25;
            ballSpeedY = -0.25;
        }
    }
}


void BrickBreaker::draw(RenderWindow& window)
{
    window.draw(paddle);
    window.draw(ball);
    window.draw(scoreText);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (brickVisible[i][j])
                window.draw(bricks[i][j]);
        }
    }

    for (int i = 0; i < lives; i++)
    {
        window.draw(hearts[i]);
    }

    if (gameEnded)
    {
        window.draw(dimOverlay);
        window.draw(endBox);
        window.draw(endTitleText);
        window.draw(endScoreText);
        window.draw(playAgainButton);
        window.draw(playAgainText);
        window.draw(mainMenuButton);
        window.draw(mainMenuText);
    }
}

void BrickBreaker::handleEvent(RenderWindow& window, Event& event, GameState& screen)
{
    if (!gameEnded)  
        return;

    if (event.type == Event::MouseButtonPressed)
    {
        Vector2i mouse = Mouse::getPosition(window);

        if (playAgainButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            resetGame();   
        }

        if (mainMenuButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            resetGame();
            screen = HUB_SCREEN;
        }
    }
}