/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef BULLET_H
#define BULLET_H

#include "ShapeObject.h"
#include "RGBColor.h"
#include "Boundary.h"

class Bullet : public ShapeObject
{
public:
    Bullet();
    Bullet(const Point& point, int delta, const RGBColor& color);

    Boundary getBoundary() const;
    void setVisible(bool value);
    bool isVisible() const;
    void move();
    void draw();

private:
    int      deltaY_;
    RGBColor color_;
    bool     visible_;
};

#endif//BULLET_H
