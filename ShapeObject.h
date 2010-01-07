/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef SHAPEOBJECT_H
#define SHAPEOBJECT_H

#include "Object.h"
#include "Point.h"
#include "RGBColor.h"
#include "Shape.h"
#include "Boundary.h"

class ShapeObject : public Object
{
public:
    explicit ShapeObject(const Point& position);
    virtual Boundary getBoundary() const = 0;
    virtual bool isVisible() const;

protected:
    void addPoint(const Point& point);
    void drawWithColor(const RGBColor& color);

private:
    Shape shape_;
};

#endif//SHAPEOBJECT_H
