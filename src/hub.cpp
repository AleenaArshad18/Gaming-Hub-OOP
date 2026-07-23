#include "Hub.h"
#include<iostream>
using namespace std;
using namespace sf;

Hub::Hub()
{
    font.loadFromFile("PixelPurl.ttf");

    // Title
    title.setFont(font);
    title.setString("Gaming Hub");
    title.setCharacterSize(120);
    title.setFillColor(Color(80, 101, 122));
    title.setPosition(260, 40);

    // TicTacToe Button
    ticTacToeButton.setSize(Vector2f(220, 60));
    ticTacToeButton.setPosition(60, 260);
    ticTacToeButton.setFillColor(Color(24, 24, 55));

    ticTacToeText.setFont(font);
    ticTacToeText.setString("Tic Tac Toe");
    ticTacToeText.setCharacterSize(36);
    ticTacToeText.setFillColor(Color::White);
    ticTacToeText.setPosition(90, 265);


    // Pong Button
    pongButton.setSize(Vector2f(220, 60));
    pongButton.setPosition(60, 340);
    pongButton.setFillColor(Color(24, 24, 55));

    pongText.setFont(font);
    pongText.setString("Ping Pong");
    pongText.setCharacterSize(36);
    pongText.setFillColor(Color::White);
    pongText.setPosition(90, 345);


    // Brick Breaker Button
    brickButton.setSize(Vector2f(220, 60));
    brickButton.setPosition(60, 420);
    brickButton.setFillColor(Color(24, 24, 55));

    brickText.setFont(font);
    brickText.setString("Brick Breaker");
    brickText.setCharacterSize(36);
    brickText.setFillColor(Color::White);
    brickText.setPosition(85, 425);


    // Leaderboard Button
    leaderboardButton.setSize(Vector2f(220, 60));
    leaderboardButton.setPosition(60, 500);
    leaderboardButton.setFillColor(Color(24, 24, 55));

    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(36);
    leaderboardText.setFillColor(Color::White);
    leaderboardText.setPosition(90, 505);

    if (!buttonClickSoundBuffer.loadFromFile("dragon-studio-button-press-382713.wav"))  
        cout << "Button click sound not loaded"<<endl;                                  
    buttonClickSound.setBuffer(buttonClickSoundBuffer);

}


void Hub::checkHover(RenderWindow& window)
{
    Vector2i mouse =Mouse::getPosition(window);

    //tic tac toe
    if (ticTacToeButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        ticTacToeButton.setFillColor(Color(120, 170, 255));
    else
        ticTacToeButton.setFillColor(Color(24, 24, 55));


    // Pong hover
    if (pongButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        pongButton.setFillColor(Color(120, 170, 255));
    else
        pongButton.setFillColor(Color(24, 24, 55));

    // Brick breaker
    if (brickButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        brickButton.setFillColor(Color(120, 170, 255));
    else
        brickButton.setFillColor(Color(24, 24, 55));

    // Leaderboard
    if (leaderboardButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        leaderboardButton.setFillColor(Color(120, 170, 255));
    else
        leaderboardButton.setFillColor(Color(24, 24, 55));
}

void Hub::handleEvent(RenderWindow& window, Event& event, GameState& screen)
{
    checkHover(window);

    if (event.type == Event::MouseButtonPressed)
    {
        Vector2i mouse = Mouse::getPosition(window);

        if (ticTacToeButton.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            buttonClickSound.play();  
            screen = TTT_NAME_SCREEN;
        }

        else if (pongButton.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            buttonClickSound.play();  
            screen = PONG_NAME_SCREEN;
        }

        else if (brickButton.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            buttonClickSound.play();   
            screen = BRICK_NAME_SCREEN;
        }

        else if (leaderboardButton.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            buttonClickSound.play(); 
            screen = LEADER_BOARD_SCREEN;
        }
    }
}

void Hub::draw(RenderWindow& window)
{
    window.draw(title);

    window.draw(ticTacToeButton);
    window.draw(ticTacToeText);

    window.draw(pongButton);
    window.draw(pongText);

    window.draw(brickButton);
    window.draw(brickText);

    window.draw(leaderboardButton);
    window.draw(leaderboardText);
}