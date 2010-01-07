/// @date 2007/07/14
/// @author E.Matsumoto

#include "Shape.h"

#include <functional>
#include <algorithm>

// @brief helper functor : add vertex
struct Vertex : public std::unary_function<const Point&, void>
{
    explicit Vertex(const Point& origin) : origin_(origin) {}

    void operator() (const Point& point)
    {
        glVertex2i(origin_.x + point.x, origin_.y + point.y);
    }

    const Point origin_;
};

void Shape::addPoint(const Point& point)
{
    points_.push_back(point);
}

void Shape::draw(const Point& position, const RGBColor& color, GLenum mode)
{
    glColor3dv(color.get());
    glBegin(mode);
    std::for_each(points_.begin(), points_.end(), Vertex(position));
    glEnd();
}
