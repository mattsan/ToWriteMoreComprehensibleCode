/// @date 2007/07/14
/// @author E.Matsumoto

#include "Alien.h"
#include "Game.h"
#include <functional>
#include <algorithm>

// @brief helper functor
struct Overlap : public std::unary_function<const ShapeObject&, bool>
{
    const Boundary& boundary;

    explicit Overlap(const Boundary& boundary) : boundary(boundary) {}

    bool operator() (const ShapeObject& object)
    {
        return object.getBoundary().overlapsWith(boundary);
    }
};

static const Point    InitialPosition(20, 20);
static const RGBColor AlienColor(1, 0.5, 0);
static const int      BulletSpeed = 10;
static const int      SpeedX      = 5;
static const int      SpeedY      = 10;

Alien::Alien() : ShapeObject(InitialPosition), speedX_(SpeedX)
{
    addPoint(Point( -5, -5));
    addPoint(Point(  5, -5));
    addPoint(Point( 10,  0));
    addPoint(Point(  5,  5));
    addPoint(Point(  2,  2));
    addPoint(Point( -2,  2));
    addPoint(Point( -5,  5));
    addPoint(Point(-10,  0));
}

Boundary Alien::getBoundary() const
{
    return Boundary(getPosition() + Point(-10, -5), getPosition() + Point(10, 5));
}

Bullet Alien::fire()
{
    return Bullet(getPosition(), BulletSpeed, AlienColor);
}

void Alien::turn()
{
    speedX_ = -speedX_;
}

void Alien::move()
{
    ShapeObject::move(Point(speedX_, 0));

    const Boundary screen = Game::getInstance().getScreen();

    if((getPosition().x < screen.getLeft()) || (screen.getRight() < getPosition().x))
    {
        turn();
        ShapeObject::move(Point(0, SpeedY));
    }
}

void Alien::draw()
{
    drawWithColor(AlienColor);
}

void Aliens::addAlien()
{
    aliens_.push_back(Alien());
}

bool Aliens::isHitBy(const ShapeObject& object)
{
    if( ! object.isVisible())
    {
        return false;
    }

    std::vector<Alien>::iterator i = std::find_if(aliens_.begin(), aliens_.end(), Overlap(object.getBoundary()));

    if(i == aliens_.end())
    {
        return false;
    }

    aliens_.erase(i);
    return true;
}

bool Aliens::hits(const ShapeObject& object)
{
    return std::find_if(bullets_.begin(), bullets_.end(), Overlap(object.getBoundary())) != bullets_.end();
}

void Aliens::clearBullets()
{
    std::vector<Bullet>().swap(bullets_);
}

void Aliens::draw()
{
    std::for_each(aliens_.begin(), aliens_.end(), std::mem_fun_ref(&Alien::draw));
    std::for_each(bullets_.begin(), bullets_.end(), std::mem_fun_ref(&Bullet::draw));
}

void Aliens::move()
{
    std::for_each(aliens_.begin(), aliens_.end(), std::mem_fun_ref(&Alien::move));
    std::for_each(bullets_.begin(), bullets_.end(), std::mem_fun_ref(&Bullet::move));
    bullets_.erase(remove_if(bullets_.begin(), bullets_.end(), std::not1(std::mem_fun_ref(&Bullet::isVisible))), bullets_.end());

    // かなり荒いコード
    // 意図はわかるが…、あとで整理
    for(std::vector<Alien>::iterator i = aliens_.begin(); i != aliens_.end(); ++i)
    {
        if((std::rand() % 20) == 0) // エイリアン1匹当たりの発射頻度
        {
            bullets_.push_back(i->fire());
        }
    }
}