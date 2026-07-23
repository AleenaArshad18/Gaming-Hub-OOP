#include "TicTacToe.h"
#include<iostream>
using namespace sf;
using namespace std;

TicTacToe::TicTacToe()
{
    font.loadFromFile("PixelPurl.ttf");

    if (!placeSoundBuffer.loadFromFile("mixkit-game-ball-tap-2073.wav"))
        cout << "Place sound not loaded\n";

    placeSound.setBuffer(placeSoundBuffer);

    if (!gameOverSoundBuffer.loadFromFile("mixkit-completion-of-a-level-2063.wav"))  
        cout << "Game over sound not loaded\n";                             

    gameOverSound.setBuffer(gameOverSoundBuffer);

    if (!buttonClickSoundBuffer.loadFromFile("dragon-studio-button-press-382713.wav"))  
        cout << "Button click sound not loaded\n";                                 
    buttonClickSound.setBuffer(buttonClickSoundBuffer);

    title.setFont(font);
    title.setString("Tic Tac Toe");
    title.setCharacterSize(105);
    title.setFillColor(Color(178, 102, 255));
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(3);
    title.setPosition(320, 20);

    exitButton.setSize(Vector2f(150, 60));
    exitButton.setPosition(40, 40);
    exitButton.setFillColor(Color(200, 80, 80));

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(45);
    exitText.setPosition(85, 38);

    resetButton.setSize(Vector2f(150, 60));
    resetButton.setPosition(40, 120);
    resetButton.setFillColor(Color(80, 150, 200));

    resetText.setFont(font);
    resetText.setString("Reset");
    resetText.setCharacterSize(45);
    resetText.setPosition(70, 115);

    resultText.setFont(font);
    resultText.setCharacterSize(60);
    resultText.setPosition(400, 530);
    resultText.setFillColor(Color(168, 119, 230));
    resultText.setOutlineColor(Color::Black);
    resultText.setOutlineThickness(0);

    justWon = false;  

    initializeBoard();
}

void TicTacToe::initializeBoard()
{
    playerXTurn = true;
    gameOver = false;
    justWon = false;  

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = ' ';
            cellText[row][col].setString("");

            cells[row][col].setSize(Vector2f(120, 120));
            cells[row][col].setFillColor(Color(73, 128, 184));
            cells[row][col].setPosition(350 + col * 130, 150 + row * 130);

            cellText[row][col].setFont(font);
            cellText[row][col].setCharacterSize(60);
            cellText[row][col].setPosition(390 + col * 130, 170 + row * 130);
        }
    }

    resultText.setString("");
}

bool TicTacToe::checkWinner(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool TicTacToe::checkDraw()
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == ' ')
                return false;
    return true;
}

void TicTacToe::resetGame()
{
    initializeBoard();
}

void TicTacToe::handleCellClick(int row, int col)
{
    if (board[row][col] != ' ' || gameOver == true)
        return;

    if (playerXTurn)
    {
        board[row][col] = 'X';
        cellText[row][col].setString("X");
    }
    else
    {
        board[row][col] = 'O';
        cellText[row][col].setString("O");
    }

    placeSound.play();

    if (checkWinner('X'))
    {
        resultText.setString(player1Name + " Wins!");
        gameOver = true;
        justWon = true;
        lastWinMessage = player1Name + " Wins!";
        gameOverSound.play();
    }
    else if (checkWinner('O'))
    {
        resultText.setString(player2Name + " Wins!");
        gameOver = true;
        justWon = true;
        lastWinMessage = player2Name + " Wins!";
        gameOverSound.play();
    }

    else if (checkDraw())
    {
        resultText.setString("Draw Game!");
        gameOver = true;
        justWon = true;                      
        lastWinMessage = "Draw Game!";        
        gameOverSound.play();
    }

    playerXTurn = !playerXTurn;
}

void TicTacToe::handleEvent(RenderWindow& window, Event& event, GameState& screen)
{
    if (event.type == Event::MouseButtonPressed)
    {
        Vector2i mouse = Mouse::getPosition(window);

        if (exitButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            buttonClickSound.play();
            resetGame();
            screen = HUB_SCREEN;
        }

        if (resetButton.getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
        {
            buttonClickSound.play();
            resetGame();
        }

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (cells[row][col].getGlobalBounds().contains((float)mouse.x, (float)mouse.y))
                {
                    handleCellClick(row, col);
                }
            }
        }
    }
}

void TicTacToe::draw(RenderWindow& window)
{
    window.draw(title);
    window.draw(exitButton);
    window.draw(exitText);
    window.draw(resetButton);
    window.draw(resetText);

    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
        {
            window.draw(cells[row][col]);
            window.draw(cellText[row][col]);
        }

    window.draw(resultText);
}