
#include "Rectangle.h"
#include "Vertex.h"
#include "Board.h"

// Constructors
Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
    setVertices(bottomLeft, topRight);
}
Rectangle::Rectangle(const Vertex vertices[2]) :
    Rectangle(vertices[0], vertices[1]) { }

Rectangle::Rectangle(double x, double y, double width, double height) :
    Rectangle(Vertex(x,y), Vertex(x + width, y + height)) { }

Rectangle::Rectangle(const Vertex& center, double width, double height) :
    Rectangle(
        Vertex(center.m_col - (width / 2), center.m_row - (height / 2)),
        Vertex(center.m_col + (width / 2), center.m_row + (height / 2))
    ) { }

// Rectangle specific functions
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
double Rectangle::getHeight() const
{
    return m_topRight.m_row - m_bottomLeft.m_row;
}

// non shape specific functions
void Rectangle::draw(Board& board) const
{
    // calculate the two missing points on the rect
    Vertex topLeft(m_bottomLeft.m_col, m_topRight.m_row);
    Vertex bottomRight(m_topRight.m_col, m_bottomLeft.m_row);

    board.drawLine(m_bottomLeft, topLeft);
    board.drawLine(m_bottomLeft, bottomRight);
    board.drawLine(m_topRight, topLeft);
    board.drawLine(m_topRight, bottomRight);
}

Rectangle Rectangle::getBoundingRectangle() const
{
    return Rectangle(m_bottomLeft, m_topRight);
}

double Rectangle::getPerimeter() const
{
    return (getWidth() + getHeight()) * 2;
}

double Rectangle::getArea() const
{
    return getWidth() * getHeight();
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
    Vertex newTopRight = scalePoint(center, m_topRight, factor);
    Vertex newBottomLeft = scalePoint(center, m_bottomLeft, factor);

   //applay the scail if the scaild rect is a valid one
    return setVertices(newBottomLeft, newTopRight);
}

// Rectangle utility functions
bool Rectangle::validRectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
    return  topRight.isValid() && bottomLeft.isValid() &&
            !bottomLeft.isToTheRightOf(topRight) &&
            !bottomLeft.isHigherThan(topRight);
}

bool Rectangle::setVertices(const Vertex &bottomLeft, const Vertex &topRight)
{
    if (validRectangle(bottomLeft, topRight))
    {
        m_topRight = topRight;
        m_bottomLeft = bottomLeft;
        return true;
    }
    return false;
}