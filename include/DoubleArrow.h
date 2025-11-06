#pragma once

#include "Rectangle.h"
#include "EquilateralTriangle.h"

class DoubleArrow
{
    DoubleArrow (const EquilateralTriangle& first, const EquilateralTriangle& second);
    DoubleArrow (const EquilateralTriangle& first, double length);

    double getLength(double index) const;
    double getHight(double index) const;
    Vertex getConnection() const;

    void draw(Board& board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);
};
