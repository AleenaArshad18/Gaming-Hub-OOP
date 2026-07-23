#include "BrickNameScreen.h"
#include <iostream>
using namespace std;
using namespace sf;

BrickNameScreen::BrickNameScreen()
{
    font.loadFromFile("PixelPurl.ttf");

    backgroundTexture.loadFromFile("new-game-background-1.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 1000.0f / backgroundTexture.getSize().x;
    float scaleY = 700.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    promptText.setFont(font);
    promptText.setCharacterSize(40);
    promptText.setFillColor(Color(178, 102, 255));
    promptText.setString("Enter Your Name:");
    promptText.setPosition(300, 230);

    inputBox.setSize(Vector2f(400, 60));
    inputBox.setPosition(300, 300);
    inputBox.setFillColor(Color(30, 30, 60));
    inputBox.setOutlineThickness(3);
    inputBox.setOutlineColor(Color(178, 102, 255));

    inputDisplay.setFont(font);
    inputDisplay.setCharacterSize(30);
    inputDisplay.setFillColor(Color::White);
    inputDisplay.setPosition(315, 315);
}

void BrickNameScreen::reset()
{
    currentInput.clear();
    playerName.clear();
    inputDisplay.setString("");
    promptText.setString("Enter Your Name:");
}

void BrickNameScreen::handleEvent(RenderWindow& window, Event& event, GameState& screen)
{
    if (event.type == Event::TextEntered)
    {
        if (event.text.unicode == '\b')
        {
            if (!currentInput.empty())
                currentInput.pop_back();
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n')
        {
            if (!currentInput.empty())
            {
                playerName = currentInput;
                currentInput.clear();
                inputDisplay.setString("");
                screen = BRICK_BREAKER_SCREEN;
            }
        }
        else if (event.text.unicode < 128 && currentInput.size() < 15)
        {
            currentInput += static_cast<char>(event.text.unicode);
        }

        inputDisplay.setString(currentInput);
    }
}

void BrickNameScreen::draw(RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(promptText);
    window.draw(inputBox);
    window.draw(inputDisplay);
}