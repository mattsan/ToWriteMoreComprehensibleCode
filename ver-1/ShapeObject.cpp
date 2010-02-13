/// @date 2007/07/14
/// @author E.Matsumoto

#include "ShapeObject.h"
#include "Game.h"

ShapeObject::ShapeObject(const Point& position) : Object(position)
{
}

bool ShapeObject::isVisible() const
{
    return Game::getInstance().getScreen().includes(getPosition());
}

void ShapeObject::drawWithColor(const RGBColor& color)
{
    shape_.draw(getPosition(), color, GL_POLYGON);
}

void ShapeObject::addPoint(const Point& point)
{
    shape_.addPoint(point);
}
