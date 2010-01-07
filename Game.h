/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef GAME_H
#define GAME_H

#include "Boundary.h"

class Ship;
class Bullet;
class Aliens;
class TextObject;

class Game
{
public:
    static const int Interval = 100;
    static const int Width    = 320;
    static const int Height   = 240;

    static Game& getInstance();

    Boundary getScreen() const;

    void onDisplay();
    void onResize(int w, int h);
    void onKey(unsigned char key, int x, int y);
    void onSpecialKey(int key, int x, int y);
    void onTimer(void (*timer)(int), int n);

private:
    Game();
    ~Game();
    Game(const Game&);
    Game& operator = (const Game&);

    void draw();

    static Game game_;

    int         width_;
    int         height_;
    int         score_;
    int         left_;
    Ship*       myShip_;
    Bullet*     myBullet_;
    Aliens*     aliens_;
    TextObject* text_;
};

#endif//GAME_H
