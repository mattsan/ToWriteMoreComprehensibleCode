/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Point.h"

#include <iosfwd>

class Boundary
{
public:
    Boundary();
    Boundary(const Point& leftTop, const Point& rightBottom);
    Boundary(int left, int top, int right, int bottom);

    const Point& getLeftTop() const;
    const Point  getRightTop() const;
    const Point  getLeftBottom() const;
    const Point& getRightBottom() const;

    const int getLeft() const   { return leftTop_.x;     }
    const int getTop() const    { return leftTop_.y;     }
    const int getRight() const  { return rightBottom_.x; }
    const int getBottom() const { return rightBottom_.y; }

    Boundary& operator += (const Boundary& boundary);
    Boundary& operator -= (const Boundary& boundary);
    Boundary& operator *= (int a);
    Boundary& operator /= (int a);

    bool includes(const Point& point) const;
    bool overlapsWith(const Boundary& boundary) const;

private:
    void rearranges();

    Point leftTop_;
    Point rightBottom_;
};

Boundary operator + (Boundary lhs, const Boundary& rhs);
Boundary operator - (Boundary lhs, const Boundary& rhs);
Boundary operator * (Boundary lhs, int rhs);
Boundary operator / (Boundary lhs, int rhs);

std::ostream& operator << (std::ostream& out, const Boundary& boundary);

#endif//BOUNDARY_H
