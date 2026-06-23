#pragma once

#include <cstdint>

class Line;
class Circle;

class IPrimitiveVisitor
{
public:
    virtual ~IPrimitiveVisitor() = default;
    virtual void Visit(const Line& line) = 0;
    virtual void Visit(const Circle& circle) = 0;
};

class IPrimitive
{
private:
    uint32_t m_id;
    static inline uint32_t m_next_id = 1;

public:
    IPrimitive() : m_id(m_next_id++) {}
    virtual ~IPrimitive() = default;

    uint32_t GetID() const { return m_id; }
    virtual void Draw() const = 0;
    virtual void Accept(IPrimitiveVisitor& visitor) const = 0;
};

