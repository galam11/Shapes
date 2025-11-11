#pragma once

#include "Rectangle.h"

class Frame
{
    // Private members
    Rectangle m_inner = Rectangle(Vertex(10, 20), Vertex(20, 30));
    Rectangle m_outer = Rectangle(Vertex(10, 20), Vertex(20, 30));

    //private utility function
    bool validFrame(Rectangle outer, Rectangle inner);

public:
    // Constructors
    Frame(const Rectangle &outer, const Rectangle &inner);
    Frame(const Rectangle &outer, double thickness);

    // Frame only functions
    Vertex getBottomLeft() const;
    Vertex getTopRight() const;
    double getThickness() const;

    // All shapes functions
    void draw(Board &board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);
};
