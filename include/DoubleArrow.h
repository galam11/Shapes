#pragma once

#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"

class DoubleArrow
{

public:

    // Constructors
    DoubleArrow (const EquilateralTriangle& first, const EquilateralTriangle& second);
    DoubleArrow (const EquilateralTriangle& first, double length);

    // DoubleArrow specific functions
    double getLength(int index) const;
    double getHeight(int index) const;
    Vertex getConnection() const;

    // non specific functions
    void draw(Board& board) const;
    Rectangle getBoundingRectangle() const;
    double getPerimeter() const;
    double getArea() const;
    Vertex getCenter() const;
    bool scale(double factor);


private:
    // Private members
    EquilateralTriangle m_triangle0 = EquilateralTriangle(Vertex(20, 20),
        Vertex(30, 20),
        Vertex(25, 20 + DEFAULT_COEFFICIENT));

    EquilateralTriangle m_triangle1 = EquilateralTriangle(Vertex(25, 20 + DEFAULT_COEFFICIENT),
        Vertex(25, 20 + DEFAULT_COEFFICIENT),
        Vertex(25, 20 + DEFAULT_COEFFICIENT));

    // Private utility functions
    Vertex getTriangleTip(const EquilateralTriangle& triangle) const;
    bool validDoubleArrow(const EquilateralTriangle& triangle0, const EquilateralTriangle& triangle1);
    bool triangleIsUp(const EquilateralTriangle& triangle);
    bool setTriangles(const EquilateralTriangle& triangle0, const EquilateralTriangle& triangle1);

};
