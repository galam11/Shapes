#pragma once

#include "Rectangle.h"

class Frame
{
private:
    Rectangle m_inner = Rectangle(Vertex(10,20), Vertex(20,30));
    Rectangle m_outer = Rectangle(Vertex(10,20), Vertex(20,30));
public:
    Frame(const Rectangle& outer, const Rectangle& inner);
    Frame(const Rectangle& outer, double thickness);

    Vertex getBottomLeft() const;
    Vertex getTopRight() const;
    double getThickness() const;

    void draw(Board& board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);

    bool validFrame(Rectangle outer, Rectangle inner);
};
