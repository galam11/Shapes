
#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"
#include "Utilities.h"
#include <cmath>

// Constructors
EquilateralTriangle::EquilateralTriangle(Vertex v0, Vertex v1, Vertex v2) :
	m_v0(20, 20), m_v1(30, 20), m_v2(25, 20 + DEFAULT_COEFFICIENT)
{
	if (validEquilateralTriangle(v0, v1, v2))
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
	}
}

EquilateralTriangle::EquilateralTriangle(const Vertex vertices[3]) :
	EquilateralTriangle(vertices[0], vertices[1], vertices[2]) { }

EquilateralTriangle::EquilateralTriangle(Vertex v, double length, bool isUp) :
	EquilateralTriangle(v,

					   (!length < 0) ? Vertex(v.m_col + length, v.m_row) 
									 : Vertex(-1, -1),

					   (!length < 0) ? Vertex(v.m_col + (length / 2),
											  v.m_row + (isUp ? (length * TRIANGLE_HEIGHT_COEFFICIENT)
															: - (length * TRIANGLE_HEIGHT_COEFFICIENT)))
									 : Vertex(-1, -1)) { }

// EquilateralTriangle only functions
Vertex EquilateralTriangle::getVertex(int index) const
{
	if (index == 0)
	{
		return m_v0;
	}
	else if (index == 1)
	{
		return m_v1;
	}
	return m_v2;
}

double EquilateralTriangle::getLength() const
{
	return distance(m_v0, m_v1);
}

double EquilateralTriangle::getHeight() const
{
	return TRIANGLE_HEIGHT_COEFFICIENT * getLength();
}

// All shapes functions

void EquilateralTriangle::draw(Board& board) const
{
	board.drawLine(m_v0, m_v1);
	board.drawLine(m_v0, m_v2);
	board.drawLine(m_v2, m_v1);
}

Rectangle EquilateralTriangle::getBoundingRectangle() const
{
	double height = getHeight();
	double length = getLength();
	double center_x = getCenter().m_col;
	double center_y = getCenter().m_row;
	Vertex bottomLeft(center_x - (length / 2), center_y - (height / 2));
	Vertex topRight(center_x + (length / 2), center_y + (height / 2));

	return Rectangle(bottomLeft, topRight);
}

double EquilateralTriangle::getPerimeter() const
{
	return 3 * getLength();
}

double EquilateralTriangle::getArea() const
{
	return (getLength() * getHeight()) / 2;
}

Vertex EquilateralTriangle::getCenter() const
{
	double x = (m_v0.m_col + m_v1.m_col + m_v2.m_col) / 3;
	double y = (m_v0.m_row + m_v1.m_row + m_v2.m_row) / 3;
	return Vertex(x, y);
}

bool EquilateralTriangle::scale(double factor)
{
	Vertex center = getCenter();
	Vertex new_v0 = scalePoint(center, m_v0, factor);
	Vertex new_v1 = scalePoint(center, m_v1, factor);
	Vertex new_v2 = scalePoint(center, m_v2, factor);

	if (validEquilateralTriangle(new_v0, new_v1, new_v2))
	{
		m_v0 = new_v0;
		m_v1 = new_v1;
		m_v2 = new_v2;

		return true;
	}
	return false;
}

// Private utility functions

bool EquilateralTriangle::validEquilateralTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

	if (!v0.isValid() || !v1.isValid() || !v2.isValid()) // check for valid point values
	{
		return false;
	}

	if (!sameRow(v0, v1) && !sameRow(v0, v2) && !sameRow(v1, v2)) // check for 2 vertices parallel to x axis
	{
		return false;
	}

	double side_1 = distance(v0, v1);
	double side_2 = distance(v0, v2);
	double side_3 = distance(v1, v2);
	if (!doubleEqual(side_1, side_2) || !doubleEqual(side_1, side_3) || !doubleEqual(side_2, side_3))
	{
		return false;
	}

	return true;
}
