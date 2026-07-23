#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Leaderboard
{
public:
    Leaderboard();

    void saveScore(string playerName, string gameName, int score);
    void draw(RenderWindow& window);
    void handleScroll(Event& event);
    void resetScroll();

private:
    Font font;
    float scrollOffset;
};

#endif