/// @date 2007/07/14
/// @author E.Matsumoto

#include "Boundary.h"
#include <algorithm>
#include <iostream>

Boundary::Boundary() : leftTop_(0, 0), rightBottom_(0, 0)
{
}

Boundary::Boundary(const Point& leftTop, const Point& rightBottom) : leftTop_(leftTop), rightBottom_(rightBottom)
{
    rearranges();
}

Boundary::Boundary(int left, int top, int right, int bottom) : leftTop_(left, top), rightBottom_(right, bottom)
{
    rearranges();
}

void Boundary::rearranges()
{
    if(rightBottom_.x < leftTop_.x) { std::swap(leftTop_.x, rightBottom_.x); }
    if(rightBottom_.y < leftTop_.y) { std::swap(leftTop_.y, rightBottom_.y); }
}

const Point& Boundary::getLeftTop() const     { return leftTop_;                          }
const Point  Boundary::getRightTop() const    { return Point(leftTop_.x, rightBottom_.y); }
const Point  Boundary::getLeftBottom() const  { return Point(rightBottom_.x, leftTop_.y); }
const Point& Boundary::getRightBottom() const { return rightBottom_;                      }

bool Boundary::includes(const Point& point) const
{
    return (leftTop_.x <= point.x) && (point.x <= rightBottom_.x) &&
           (leftTop_.y <= point.y) && (point.y <= rightBottom_.y);
}

bool Boundary::overlapsWith(const Boundary& boundary) const
{
    return includes(boundary.getLeftTop())    || includes(boundary.getRightTop())    ||
           includes(boundary.getLeftBottom()) || includes(boundary.getRightBottom()) ||
           boundary.includes(getLeftTop())    || boundary.includes(getRightTop())    ||
           boundary.includes(getLeftBottom()) || boundary.includes(getRightBottom()); 
}

Boundary& Boundary::operator += (const Boundary& boundary)
{
    leftTop_     += boundary.leftTop_;
    rightBottom_ += boundary.rightBottom_;
    return *this;
}

Boundary& Boundary::operator -= (const Boundary& boundary)
{
    leftTop_     -= boundary.leftTop_;
    rightBottom_ -= boundary.rightBottom_;
    return *this;
}

Boundary& Boundary::operator *= (int a)
{
    leftTop_     *= a;
    rightBottom_ *= a;
    return *this;
}

Boundary& Boundary::operator /= (int a)
{
    leftTop_     /= a;
    rightBottom_ /= a;
    return *this;
}

Boundary operator + (Boundary lhs, const Boundary& rhs) { lhs += rhs; return lhs; }
Boundary operator - (Boundary lhs, const Boundary& rhs) { lhs -= rhs; return lhs; }
Boundary operator * (Boundary lhs, int rhs)             { lhs *= rhs; return lhs; }
Boundary operator / (Boundary lhs, int rhs)             { lhs /= rhs; return lhs; }

std::ostream& operator << (std::ostream& out, const Boundary& boundary)
{
    return out << boundary.getLeftTop() << "-" << boundary.getRightBottom();
}
