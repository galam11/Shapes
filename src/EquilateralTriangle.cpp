
#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"
#include "Utilities.h"

// Constructors
EquilateralTriangle::EquilateralTriangle(Vertex v0, Vertex v1, Vertex v2) //האם להוסיף &?
{
	setVertices(v0, v1, v2);
}

EquilateralTriangle::EquilateralTriangle(const Vertex vertices[3]) :
	EquilateralTriangle(vertices[0], vertices[1], vertices[2]) { }

EquilateralTriangle::EquilateralTriangle(Vertex v, double length, bool isUp)
{
	Vertex v0, v1, v2;
	v0 = v;
	if (!length < 0)
	{
		v1 = Vertex(v.m_col + length, v.m_row);

		double v2_y = v.m_row;
		v2_y += (isUp ? 1 : -1) * (length * TRIANGLE_HEIGHT_COEFFICIENT);
		v2 = Vertex(v.m_col + (length / 2), v2_y);
	}
	setVertices(v0, v1, v2);
}

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
	board.drawLine(m_v1, m_v2);
}

Rectangle EquilateralTriangle::getBoundingRectangle() const
{
	double min_x = minValue(m_v0.m_col, m_v1.m_col);
	min_x = minValue(min_x, m_v2.m_col);

	double min_y = minValue(m_v0.m_row, m_v1.m_row);
	min_y = minValue(min_y, m_v2.m_row);

	return Rectangle(min_x, min_y, getLength(), getHeight());
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

	return setVertices(new_v0, new_v1, new_v2);
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

bool EquilateralTriangle::setVertices(Vertex& v0, Vertex& v1, Vertex& v2)
{
	if (validEquilateralTriangle(v0, v1, v2))
	{
		m_v0 = v0;
		m_v1 = v1;
		m_v2 = v2;
		return true;
	}
	return false;
}
