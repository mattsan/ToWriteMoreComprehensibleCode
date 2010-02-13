/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef ALIEN_H
#define ALIEN_H

#include <vector>

#include "Boundary.h"
#include "ShapeObject.h"
#include "Bullet.h"

class Alien : public ShapeObject
{
public:
    Alien();
    Boundary getBoundary() const;
    Bullet fire();
    void turn();
    void move();
    void draw();

private:
    int speedX_;
};

class Aliens
{
public:
    void addAlien();
    bool isHitBy(const ShapeObject& object);
    bool hits(const ShapeObject& object);
    void clearBullets();
    void draw();
    void move();

private:
    std::vector<Alien>  aliens_;
    std::vector<Bullet> bullets_;
};

#endif//ALIEN_H
