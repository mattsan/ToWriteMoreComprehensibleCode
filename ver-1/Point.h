/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef POINT_H
#define POINT_H

#include <iosfwd>

struct Point
{
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    Point& operator += (const Point& point) { x += point.x; y += point.y; return *this; }
    Point& operator -= (const Point& point) { x -= point.x; y -= point.y; return *this; }
    Point& operator *= (int a)              { x *= a;       y *= a;       return *this; }
    Point& operator /= (int a)              { x /= a;       y /= a;       return *this; }
};

Point operator + (Point lhs, const Point& rhs);
Point operator - (Point lhs, const Point& rhs);
Point operator * (Point lhs, int rhs);
Point operator / (Point lhs, int rhs);

std::ostream& operator << (std::ostream& out, const Point& point);

#endif//POINT_H
