#pragma once

#include "IPrimitive.h"

struct Point
{
    double x, y;
};

class Line : public IPrimitive
{
private:
    Point start{0.0, 0.0}, end{0.0, 0.0};

public:
    Line() : IPrimitive(), start{0.0, 0.0}, end{0.0, 0.0} {}
    Line(Point s, Point e) : start(s), end(e) {}

    void Draw() const override;
    void Accept(IPrimitiveVisitor& visitor) const override;
};

class Circle : public IPrimitive
{
private:
    Point center{0.0, 0.0};
    double radius{0.0};

public:
    Circle() : IPrimitive(), center{0.0, 0.0}, radius{0.0} {}
    Circle(Point c, double r) : center(c), radius(r) {}

    void Draw() const override;
    void Accept(IPrimitiveVisitor& visitor) const override;
};
