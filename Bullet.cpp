/// @date 2007/07/14
/// @author E.Matsumoto

#include "Bullet.h"

Bullet::Bullet() : ShapeObject(Point(0, 0)), deltaY_(0), color_(), visible_(false)
{
}

Bullet::Bullet(const Point& point, int delta, const RGBColor& color) :
    ShapeObject(point), deltaY_(delta), color_(color), visible_(true)
{
    addPoint(Point(-3,  -5));
    addPoint(Point( 0, -10));
    addPoint(Point( 3,  -5));
    addPoint(Point( 0,   0));
}

Boundary Bullet::getBoundary() const
{
    return Boundary(getPosition() + Point(-3, -10), getPosition() + Point(3, 0));
}

void Bullet::setVisible(bool value)
{
    visible_ = value;
}

bool Bullet::isVisible() const
{
    return visible_;
}

void Bullet::move()
{
    if(visible_)
    {
        ShapeObject::move(Point(0, deltaY_));
        visible_ = ShapeObject::isVisible();
    }
}

void Bullet::draw()
{
    if(visible_)
    {
        drawWithColor(color_);
    }
}
