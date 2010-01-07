/// @date 2007/07/14
/// @author E.Matsumoto

#include "Ship.h"
#include "Game.h"

static const int Delta = 10;

Ship::Ship(const Point& position) : ShapeObject(position)
{
    addPoint(Point(-10,   0));
    addPoint(Point(  0, -10));
    addPoint(Point( 10,   0));
    addPoint(Point( 10,  10));
    addPoint(Point(-10,  10));
}

Boundary Ship::getBoundary() const
{
    return Boundary(getPosition() + Point(-10, 0), getPosition() + Point(10, 10));
}

void Ship::moveLeft()  { move(Point(-Delta, 0)); }
void Ship::moveRight() { move(Point(+Delta, 0)); }
void Ship::moveUp()    { move(Point(0, -Delta)); }
void Ship::moveDown()  { move(Point(0, +Delta)); }

Bullet Ship::fire()
{
    return Bullet(getPosition(), -10, RGBColor(0, 0, 1));
}

void Ship::draw()
{
    drawWithColor(RGBColor(0, 0, 1));
}
