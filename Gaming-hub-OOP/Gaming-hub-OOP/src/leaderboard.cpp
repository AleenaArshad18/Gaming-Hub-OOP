#include "leaderboard.h"
#include <fstream>
using namespace sf;
using namespace std;

Leaderboard::Leaderboard()
{
    font.loadFromFile("PixelPurl.ttf");
    scrollOffset = 0.f;
}

void Leaderboard::saveScore(string playerName, string gameName, int score)
{
    ofstream file("leaderboard.txt", ios::app);
    if (file.is_open())
    {
        file << playerName << "  " << gameName << "  " << score << endl;
    }
    file.close();
}

void Leaderboard::resetScroll()
{
    scrollOffset = 0.f;
}

void Leaderboard::handleScroll(Event& event)
{
    if (event.type == Event::MouseWheelScrolled)
    {
        scrollOffset -= event.mouseWheelScroll.delta * 30.f;
        if (scrollOffset < 0.f)
            scrollOffset = 0.f;
    }
}

void Leaderboard::draw(RenderWindow& window)
{
    Text title;
    title.setFont(font);
    title.setString("Leaderboard");
    title.setCharacterSize(60);
    title.setFillColor(Color(178, 102, 255));
    title.setPosition(320, 30);
    window.draw(title);

    ifstream file("leaderboard.txt");
    string line;
    float yOffset = 150.f - scrollOffset;

    while (getline(file, line))
    {
        if (yOffset > 120.f && yOffset < 700.f)
        {
            Text entry;
            entry.setFont(font);
            entry.setString(line);
            entry.setCharacterSize(30);
            entry.setFillColor(Color::White);
            entry.setPosition(100, yOffset);
            window.draw(entry);
        }
        yOffset += 45.f;
    }

    file.close();
}