/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef SHAPE_H
#define SHAPE_H

#include "RGBColor.h"
#include "Point.h"
#include <vector>
#include <GLUT/glut.h>

typedef std::vector<Point> Points;

class Shape
{
public:
    void addPoint(const Point& point);
    void draw(const Point& position, const RGBColor& color, GLenum mode);

private:
    Points points_;
};

#endif//SHAPE_H
