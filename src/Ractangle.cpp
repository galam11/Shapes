
#include "Rectangle.h"
#include "Vertex.h"
#include "Board.h"

//constractors
Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight) :
    m_bottomLeft(Vertex(20,10)), m_topRight(Vertex(30, 20))
{
    if (validRectangle(bottomLeft, topRight))
    {
      m_bottomLeft = bottomLeft;
      m_topRight = topRight;
    }
}
Rectangle::Rectangle(const Vertex vertices[2]) :
    Rectangle(vertices[0], vertices[1]) { }

Rectangle::Rectangle(double x, double y, double width, double hight) :
    Rectangle(Vertex(x,y), Vertex(x + width, y + hight)) { }

Rectangle::Rectangle(const Vertex& center, double width, double hight) :
    Rectangle(center, Vertex(center.m_col + width, center.m_row + hight)) { }

// rectangle only functions
Vertex Rectangle::getBottomLeft() const
{
    return m_bottomLeft;
}

Vertex Rectangle::getTopRight() const
{
    return m_topRight;
}

double Rectangle::getWidth() const
{
    return m_topRight.m_col - m_bottomLeft.m_col;
}
double Rectangle::getHight() const
{
    return m_topRight.m_row - m_bottomLeft.m_row;
}

// all shapes functions

void Rectangle::draw(Board& bord) const
{
    // calcuilating the two mising points on the rect
    Vertex topLeft(m_bottomLeft.m_col, m_topRight.m_row);
    Vertex bottomRight(m_topRight.m_col, m_bottomLeft.m_row);

    bord.drawLine(m_bottomLeft, topLeft);
    bord.drawLine(m_bottomLeft, bottomRight);

    bord.drawLine(m_topRight, topLeft);
    bord.drawLine(m_topRight, bottomRight);
}

Rectangle Rectangle::getBoundingRectangle() const
{
    return Rectangle(m_bottomLeft, m_topRight);
}

double Rectangle::getPerimeter() const
{
    return (getWidth() + getHight()) * 2;
}

double Rectangle::getArea() const
{
    return getWidth() * getHight();
}

Vertex Rectangle::getCenter() const
{
    return Vertex(
      (m_bottomLeft.m_col + m_topRight.m_col) / 2 ,
      (m_bottomLeft.m_row + m_topRight.m_row) / 2
    );
}

bool Rectangle::scale(double factor)
{
    Vertex center = getCenter();
    Vertex newTopRight = m_topRight.scalePointFromCenter(center, factor);
    Vertex newBottomLeft = m_bottomLeft.scalePointFromCenter(center, factor);

   if (validRectangle(newBottomLeft, newTopRight))
   {
       m_topRight = newTopRight;
       m_bottomLeft = newBottomLeft;

       return true;
   }
   return false;
}

// private utility functions

bool Rectangle::validRectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
    return topRight.isValid() &&
        bottomLeft.isValid() &&
        topRight.isToTheRightOf(bottomLeft) &&
        topRight.isHigherThan(bottomLeft);
}

