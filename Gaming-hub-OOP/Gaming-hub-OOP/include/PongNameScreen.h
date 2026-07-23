#pragma once
#include <SFML/Graphics.hpp>
#include "Hub.h"
#include <string>
using namespace sf;
using namespace std;

class PongNameScreen
{
public:
    PongNameScreen();

    void handleEvent(RenderWindow& window, Event& event, GameState& screen);
    void draw(RenderWindow& window);

    void reset();  

    string getPlayer1Name() const { return player1Name.empty() ? "Player 1" : player1Name; }
    string getPlayer2Name() const { return player2Name.empty() ? "Player 2" : player2Name; }

private:
    Font font;

    Texture backgroundTexture;
    Sprite  backgroundSprite;

    Text promptText;     
    RectangleShape inputBox;
    Text inputDisplay;

    string currentInput;  
    string player1Name;   
    string player2Name;   

    int stage; 
};