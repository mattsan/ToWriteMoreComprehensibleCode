/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef SHIP_H
#define SHIP_H

#include "ShapeObject.h"
#include "Bullet.h"
#include "Boundary.h"

class Ship : public ShapeObject
{
public:
    Ship(const Point& position);

    Boundary getBoundary() const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    Bullet fire();
    void draw();
};

#endif//SHIP_H
