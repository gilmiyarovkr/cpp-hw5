#include "include/Primitive.h"
#include <iostream>

void Line::Draw() const
{
    std::cout << "Draw Line!";
}

void Line::Accept(IPrimitiveVisitor& visitor) const
{
    visitor.Visit(*this);
}

void Circle::Draw() const
{
    std::cout << "Draw Circle!";
}

void Circle::Accept(IPrimitiveVisitor& visitor) const
{
    visitor.Visit(*this);
}
