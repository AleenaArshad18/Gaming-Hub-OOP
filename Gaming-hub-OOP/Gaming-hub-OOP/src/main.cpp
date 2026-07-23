#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Hub.h"
#include "TicTacToe.h"
#include "PongNameScreen.h"
#include "pong.h"
#include "BrickNameScreen.h"
#include "brick-breaker.h"
#include "leaderboard.h"
#include "TicTacToeNameScreen.h"
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 700), "Gaming Hub");

    GameState currentScreen = HUB_SCREEN;

    Hub hub;
    TicTacToe ticTacToe;
    PongNameScreen pongNameScreen;
    TicTacToeNameScreen tictactoeNameScreen;
    PingPong pong;
    BrickNameScreen brickNameScreen;
    BrickBreaker brickBreaker;
    Leaderboard leaderboard;
    Clock clock;

    // Background music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("tatamusic-game-gaming-video-game-music-482380.wav"))
        cout << "Background music not loaded\n";
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(60);  
    backgroundMusic.play();

    // Hub background
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("hub-background3.0.jpg"))
        cout << "Hub background not loaded";
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 1000.0f / backgroundTexture.getSize().x;
    float scaleY = 700.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Tic Tac Toe background
    Texture tttBackgroundTexture;
    if (!tttBackgroundTexture.loadFromFile("new-game-background-1.jpg"))
        cout << "TTT background not loaded";
    Sprite tttBackground;
    tttBackground.setTexture(tttBackgroundTexture);
    float scaleX2 = 1000.0f / tttBackgroundTexture.getSize().x;
    float scaleY2 = 700.0f / tttBackgroundTexture.getSize().y;
    tttBackground.setScale(scaleX2, scaleY2);

    // Ping Pong background
    Texture pppBackgroundTexture;
    if (!pppBackgroundTexture.loadFromFile("new-game-background-1.jpg"))
        cout << "Pong background not loaded";
    Sprite pppBackground;
    pppBackground.setTexture(pppBackgroundTexture);
    float scaleX3 = 1000.0f / pppBackgroundTexture.getSize().x;
    float scaleY3 = 700.0f / pppBackgroundTexture.getSize().y;
    pppBackground.setScale(scaleX3, scaleY3);

    // Brick Breaker background
    Texture bbbBackgroundTexture;
    if (!bbbBackgroundTexture.loadFromFile("new-game-background-1.jpg"))
        cout << "Brick Breaker background not loaded";
    Sprite bbbBackground;
    bbbBackground.setTexture(bbbBackgroundTexture);
    float scaleX4 = 1000.0f / bbbBackgroundTexture.getSize().x;
    float scaleY4 = 700.0f / bbbBackgroundTexture.getSize().y;
    bbbBackground.setScale(scaleX4, scaleY4);

    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            GameState previousScreen = currentScreen;

            // HUB
            if (currentScreen == HUB_SCREEN)
            {
                hub.handleEvent(window, event, currentScreen);
            }

            // tic tac toe
            else if (currentScreen == TTT_NAME_SCREEN)
            {
                tictactoeNameScreen.handleEvent(window, event, currentScreen);

                if (currentScreen == TIC_TAC_TOE_SCREEN)
                {
                    ticTacToe.setPlayerNames(tictactoeNameScreen.getPlayer1Name(),
                        tictactoeNameScreen.getPlayer2Name());
                }
            }
            else if (currentScreen == TIC_TAC_TOE_SCREEN)
            {
                ticTacToe.handleEvent(window, event, currentScreen);

                
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                        currentScreen = HUB_SCREEN;
                
            }

            // PING PONG
            else if (currentScreen == PONG_NAME_SCREEN)
            {
                pongNameScreen.handleEvent(window, event, currentScreen);

                if (currentScreen == PONG_SCREEN)
                {
                    pong.setPlayerNames(pongNameScreen.getPlayer1Name(),
                        pongNameScreen.getPlayer2Name());
                }
            }
            else if (currentScreen == PONG_SCREEN)
            {
                pong.handleEvent(window, event, currentScreen);

                if (!pong.isShowingWinOverlay())
                {
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                        currentScreen = HUB_SCREEN;
                }
            }

            // BRICK BREAKER
            else if (currentScreen == BRICK_NAME_SCREEN)
            {
                brickNameScreen.handleEvent(window, event, currentScreen);

                if (currentScreen == BRICK_BREAKER_SCREEN)
                {
                    brickBreaker.setPlayerName(brickNameScreen.getPlayerName());
                    brickBreaker.resetGame();
                }
            }
            else if (currentScreen == BRICK_BREAKER_SCREEN)
            {
                brickBreaker.handleEvent(window, event, currentScreen);

                if (!brickBreaker.isGameEnded())
                {
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                        currentScreen = HUB_SCREEN;
                }
            }

            // LEADERBOARD
            else if (currentScreen == LEADER_BOARD_SCREEN)
            {
                leaderboard.handleScroll(event);

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                    currentScreen = HUB_SCREEN;
            }

            //SCREEN TRANSITION 

            // Hub to Tic Tac Toe name screen
            if (previousScreen == HUB_SCREEN && currentScreen == TTT_NAME_SCREEN)
                tictactoeNameScreen.reset();

            // Name screen to Tic Tac Toe game
            if (previousScreen == TTT_NAME_SCREEN && currentScreen == TIC_TAC_TOE_SCREEN)
                ticTacToe.resetGame();

            // Hub to Pong name screen
            if (previousScreen == HUB_SCREEN && currentScreen == PONG_NAME_SCREEN)
                pongNameScreen.reset();

            // Pong Play Again to name screen
            if (previousScreen == PONG_SCREEN && currentScreen == PONG_NAME_SCREEN)
                pongNameScreen.reset();

            // Hub to Brick name screen
            if (previousScreen == HUB_SCREEN && currentScreen == BRICK_NAME_SCREEN)
                brickNameScreen.reset();

            // Brick Play Again to name screen 
            if (previousScreen == BRICK_BREAKER_SCREEN && currentScreen == BRICK_NAME_SCREEN)
                brickNameScreen.reset();

            // Leaderboard: reset scroll on fresh entry
            if (previousScreen != LEADER_BOARD_SCREEN && currentScreen == LEADER_BOARD_SCREEN)
                leaderboard.resetScroll();
        }

        if (currentScreen == PONG_SCREEN)
        {
            pong.handleInput();
            pong.update(leaderboard);
        }
        else if (currentScreen == BRICK_BREAKER_SCREEN)
        {
            brickBreaker.handleInput();
            brickBreaker.update(leaderboard);
        }

        // lower background music volume while inside any game/game-related screen,
        // and full volume while on the Hub main menu
        if (currentScreen == HUB_SCREEN)
            backgroundMusic.setVolume(60);
        else
            backgroundMusic.setVolume(20);
        
        //draw
        if (currentScreen == HUB_SCREEN)
        {
            window.draw(backgroundSprite);
            hub.draw(window);
        }
        else if (currentScreen == TTT_NAME_SCREEN)
        {
            tictactoeNameScreen.draw(window);
        }

        else if (currentScreen == TIC_TAC_TOE_SCREEN)
        {
            window.draw(tttBackground);
            ticTacToe.draw(window);
        }
        
        else if (currentScreen == PONG_NAME_SCREEN)
        {
            pongNameScreen.draw(window);
        }
        else if (currentScreen == PONG_SCREEN)
        {
            window.draw(pppBackground);
            pong.draw(window);
        }
        else if (currentScreen == BRICK_NAME_SCREEN)
        {
            brickNameScreen.draw(window);
        }
        else if (currentScreen == BRICK_BREAKER_SCREEN)
        {
            window.draw(bbbBackground);
            brickBreaker.draw(window);
        }
        else if (currentScreen == LEADER_BOARD_SCREEN)
        {
            window.draw(backgroundSprite);
            leaderboard.draw(window);
        }

        window.display();
    }

    return 0;
}