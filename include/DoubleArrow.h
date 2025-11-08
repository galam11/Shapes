#pragma once

#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"

class DoubleArrow
{
private: // Private members
    EquilateralTriangle m_et0, m_et1;

public:

    // Constructors
    DoubleArrow (const EquilateralTriangle& first, const EquilateralTriangle& second);
    DoubleArrow (const EquilateralTriangle& first, double length);

    // DoubleArrow only functions
    double getLength(double index) const;
    double getHeight(double index) const;
    Vertex getConnection() const;

    // All shapes functions
    void draw(Board& board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);

    // Private utility functions
private:
    bool validDoubleArrow(const EquilateralTriangle& et0, const EquilateralTriangle& et1);
};
