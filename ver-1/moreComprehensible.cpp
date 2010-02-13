/// @date 2007/07/02
/// @author E.Matsumoto

#include "Game.h"

#include <GLUT/glut.h>

void display()
{
    Game::getInstance().onDisplay();
}

void resize(int w, int h)
{
    Game::getInstance().onResize(w, h);
}

void key(unsigned char key, int x, int y)
{
    Game::getInstance().onKey(key, x, y);
}

void specialKey(int key, int x, int y)
{
    Game::getInstance().onSpecialKey(key, x, y);
}

void timer(int n)
{
    Game::getInstance().onTimer(timer, n);
}


void initWindow(int argc, char* argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(Game::Width, Game::Height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow("to write more comprehensible code");

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void initEvent()
{
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutTimerFunc(Game::Interval, timer, 0);
}

int main(int argc, char* argv[])
{
    initWindow(argc, argv);
    initEvent();

    glutMainLoop();

    return 0;
}
