#pragma once

#include "Rectangle.h"

class Frame
{

public:
    // Constructors
    Frame(const Rectangle &outer, const Rectangle &inner);
    Frame(const Rectangle &outer, double thickness);

    // Frame specific functions
    Vertex getBottomLeft() const;
    Vertex getTopRight() const;
    double getThickness() const;

    // non shape-specific functions
    void draw(Board &board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);

private:
    // Private members
    Rectangle m_inner = Rectangle(Vertex(10, 20), Vertex(20, 30));
    Rectangle m_outer = Rectangle(Vertex(10, 20), Vertex(20, 30));

    //private utility function
    bool validFrame(const Rectangle& outer, const Rectangle& inner);
    bool setRectangles(const Rectangle& outer, const Rectangle& inner);
};
