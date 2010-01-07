/// @date 2007/07/14
/// @author E.Matsumoto

#include "Point.h"
#include <iostream>

Point operator + (Point lhs, const Point& rhs) { lhs += rhs; return lhs; }
Point operator - (Point lhs, const Point& rhs) { lhs -= rhs; return lhs; }
Point operator * (Point lhs, int rhs)          { lhs *= rhs; return lhs; }
Point operator / (Point lhs, int rhs)          { lhs /= rhs; return lhs; }

std::ostream& operator << (std::ostream& out, const Point& point)
{
    return out << "(" << point.x << ", " << point.y << ")";
}
