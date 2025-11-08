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
    double getLength(int index) const;
    double getHeight(int index) const;
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

    Vertex getTriangleTip(const EquilateralTriangle& triangle) const;
    bool validDoubleArrow(const EquilateralTriangle& et0, const EquilateralTriangle& et1);
    bool triangleIsUp(const EquilateralTriangle& triangle);
};
