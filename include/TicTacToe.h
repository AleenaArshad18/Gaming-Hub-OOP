#include <SFML/Graphics.hpp>
#include "Hub.h"
#include <string>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

class TicTacToe
{
private:
    char board[3][3];
    bool playerXTurn;
    bool gameOver;

    void initializeBoard();
    void handleCellClick(int row, int col);
    bool checkWinner(char player);
    bool checkDraw();

    Font font;
    Text title;

    RectangleShape exitButton;
    Text exitText;

    RectangleShape resetButton;
    Text resetText;

    RectangleShape cells[3][3];
    Text cellText[3][3];

    Text resultText;

    SoundBuffer placeSoundBuffer;
    Sound placeSound;

    SoundBuffer gameOverSoundBuffer;  
    Sound gameOverSound;

    SoundBuffer buttonClickSoundBuffer;  
    Sound buttonClickSound;

    string lastWinMessage;
    bool justWon;

    string player1Name;
    string player2Name;



public:
    TicTacToe();

    void resetGame();
    void handleEvent(RenderWindow& window, Event& event, GameState& screen);
    void draw(RenderWindow& window);

    bool didJustWin() const { return justWon; }
    string getWinMessage() const { return lastWinMessage; }
    void clearJustWon() { justWon = false; }

    void setPlayerNames(const string& p1, const string& p2)
    {
        player1Name = p1;
        player2Name = p2;
    }

    string getPlayer1Name() {
        return player1Name;
    }

    string getPlayer2Name() {
        return player2Name;
    }
};
