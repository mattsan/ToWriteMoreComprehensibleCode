/// @date 2007/07/14
/// @author E.Matsumoto

#include "Game.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "TextObject.h"

#include <GLUT/glut.h>
#include <sstream>
#include <iomanip>

static const Point ShipPosition(Game::Width / 2, Game::Height / 2);
static const Point TextPosition(10, 12);
static const int   PointPerAlien = 10;

Game Game::game_;

Game::Game() : width_(Width), height_(Height), score_(0), left_(2), myShip_(0), myBullet_(0), aliens_(0)
{
    myShip_   = new Ship(ShipPosition);
    myBullet_ = new Bullet();
    aliens_   = new Aliens();
    text_     = new TextObject(TextPosition);
}

Game::~Game()
{
    delete text_;
    delete aliens_;
    delete myBullet_;
    delete myShip_;
}

Game& Game::getInstance()
{
    return game_;
}

Boundary Game::getScreen() const
{
    return Boundary(0, 0, width_, height_);
}

void Game::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    myShip_->draw();
    myBullet_->draw();
    aliens_->draw();
    text_->draw();

    glutSwapBuffers();
}

void Game::onDisplay()
{
    draw();
}

void Game::onResize(int w, int h)
{
    glViewport(0, 0, w, h);
    width_  = w;
    height_ = h;
    glLoadIdentity();
    glOrtho(-0.5, w - 0.5, h - 0.5, -0.5, -1.0, 1.0);
}

void Game::onKey(unsigned char key, int, int)
{
    switch(key)
    {
    case ' ':
        if( ! myBullet_->isVisible())
        {
            *myBullet_ = myShip_->fire();
        }
        break;

    case 'q':
    case 'Q':
    case '\033':
        std::exit(0);
        break;

    default:
        break;
    }
}

void Game::onSpecialKey(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:  myShip_->moveLeft();  break;
    case GLUT_KEY_UP:    myShip_->moveUp();    break;
    case GLUT_KEY_RIGHT: myShip_->moveRight(); break;
    case GLUT_KEY_DOWN:  myShip_->moveDown();  break;
    default:                                   break;
    }
}

void Game::onTimer(void(*timer)(int), int)
{
    // 移動
    myBullet_->move();
    aliens_->move();

    // 新たなエイリアン出現
    if((std::rand() % 20) == 0) // エイリアン発生頻度
    {
        aliens_->addAlien();
    }

    // エイリアンの当り判定
    if(aliens_->isHitBy(*myBullet_))
    {
        score_ += PointPerAlien;
        myBullet_->setVisible(false);
    }

    // 自機の当り判定
    bool myShipIsHit = aliens_->hits(*myShip_);

    // スコア文字更新
    std::ostringstream oss;
    oss.fill('0');
    oss << "SCORE : " << std::setw(6) << score_ << " / LEFT : " << left_;
    text_->set(oss.str());

    // 背景色指定
    const RGBColor clearColor = myShipIsHit ? RGBColor(1.0, 0.8, 0.8) : RGBColor(1.0, 1.0, 1.0);
    glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), 1.0);

    // 描画
    draw();

    int interval = Interval;

    // 終了判定
    if(myShipIsHit)
    {
        if(left_ == 0)
        {
            return;
        }
        --left_;
        aliens_->clearBullets();
        interval *= 10;
    }

    glutTimerFunc(interval, timer, 0);
}
