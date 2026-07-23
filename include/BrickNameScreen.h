#pragma once
#include <SFML/Graphics.hpp>
#include "Hub.h"
#include <string>
using namespace sf;
using namespace std;

class BrickNameScreen
{
public:
    BrickNameScreen();

    void handleEvent(RenderWindow& window, Event& event, GameState& screen);
    void draw(RenderWindow& window);
    void reset();

    string getPlayerName() const { return playerName.empty() ? "Player" : playerName; }

private:
    Font font;

    Texture backgroundTexture;
    Sprite  backgroundSprite;

    Text promptText;
    RectangleShape inputBox;
    Text inputDisplay;

    string currentInput;
    string playerName;
};
