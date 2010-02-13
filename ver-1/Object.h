/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef OBJECT_H
#define OBJECT_H

#include "Point.h"

class Object
{
public:
    explicit Object(const Point& position) : position_(position) {}
    virtual ~Object() {}
    const Point& getPosition() const { return position_; }
    void setPosition(const Point& position) { position_ = position; }
    void move(const Point& delta) { position_ += delta; }
    virtual void draw() = 0;

private:
    Point position_;
};

#endif//OBJECT_H
