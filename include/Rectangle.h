#pragma once

#include "Vertex.h"
#include "Board.h"
/* test */
class Rectangle {
private: // private members
  Vertex m_bottomLeft, m_topRight;
public:

  //constractors
  Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
  Rectangle(const Vertex vertices[2]);
  Rectangle(double x, double y, double width, double hight);
  Rectangle(const Vertex& center, double width, double hight);

  // rectangle only functions
  Vertex getBottomLeft() const;
  Vertex getTopRight() const;
  double getWidth() const;
  double getHight() const;

  // all shapes functions
  void draw(Board& bord) const;
  Rectangle getBoundingRectangle() const;
  double getPerimeter() const;
  double getArea() const;
  Vertex getCenter() const;
  bool scale(double factor);

  // private utility functions
private:
  bool validRectangle(const Vertex& bottomLeft, const Vertex& topRight);
};
