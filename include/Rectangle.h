#pragma once

#include "Vertex.h"
#include "Board.h"

class Rectangle {

private: // Private members

  Vertex m_bottomLeft = Vertex(20 ,10);
  Vertex m_topRight = Vertex(30, 20);

public:

  // Constructors
  Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
  Rectangle(const Vertex vertices[2]);
  Rectangle(double x, double y, double width, double height);
  Rectangle(const Vertex& center, double width, double height);

  // Rectangle only functions
  Vertex getBottomLeft() const;
  Vertex getTopRight() const;
  double getWidth() const;
  double getHeight() const;

  // All shapes functions
  void draw(Board& board) const;
  Rectangle getBoundingRectangle() const;
  double getPerimeter() const;
  double getArea() const;
  Vertex getCenter() const;
  bool scale(double factor);

  // Rectangle utility functions
  bool validRectangle(const Vertex& bottomLeft, const Vertex& topRight);
};


