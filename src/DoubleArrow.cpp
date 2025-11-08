#include "DoubleArrow.h"
#include "Board.h"
#include "Vertex.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"
#include <cmath>
#include "macros.h"
#include "Utilities.h"

// Constructors
DoubleArrow::DoubleArrow (const EquilateralTriangle& first, const EquilateralTriangle& second) :
	m_et0(Vertex(20, 20),
		  Vertex(30, 20),
		  Vertex(25, 20 + DEFAULT_COEFFICIENT)),
	m_et1(Vertex(25, 20 + DEFAULT_COEFFICIENT),
		  Vertex(25, 20 + DEFAULT_COEFFICIENT),
		  Vertex(25, 20 + DEFAULT_COEFFICIENT)) 
{
	if (validDoubleArrow(first, second))
	{
		m_et0 = first;
		m_et1 = second;
	}
}

DoubleArrow::DoubleArrow (const EquilateralTriangle& first, double length) :
	m_et0(Vertex(20, 20),
		Vertex(30, 20),
		Vertex(25, 20 + DEFAULT_COEFFICIENT)),
	m_et1(Vertex(25, 20 + DEFAULT_COEFFICIENT),
		Vertex(25, 20 + DEFAULT_COEFFICIENT),
		Vertex(25, 20 + DEFAULT_COEFFICIENT))
{
	Vertex first_tri_tip = getTriangleTip(first);

	Vertex second_tri_left(first_tri_tip.m_col - (length / 2), first_tri_tip.m_row);
	Vertex second_tri_right(first_tri_tip.m_col + (length / 2), first_tri_tip.m_row);

	Vertex second_tri_tip(first_tri_tip.m_col, first_tri_tip.m_row);
	double second_tri_height = TRIANGLE_HEIGHT_COEFFICIENT * length;
	second_tri_tip.m_row += (triangleIsUp(first) ? second_tri_height : -second_tri_height);

	EquilateralTriangle second(second_tri_left, second_tri_right, second_tri_tip);

	if (validDoubleArrow(first, second))
	{
		m_et0 = first;
		m_et1 = second;
	}
}

// DoubleArrow only functions
double DoubleArrow::getLength(int index) const
{
	return (index == 0) ? m_et0.getLength() : m_et1.getLength();
}

double DoubleArrow::getHeight(int index) const
{
	return (index == 0) ? m_et0.getHeight() : m_et1.getHeight();
}

Vertex DoubleArrow::getConnection() const
{
	return getTriangleTip(m_et0);
}

// All shapes functions

void DoubleArrow::draw(Board& board) const
{
	m_et0.draw(board);
	m_et1.draw(board);
}

Rectangle DoubleArrow::getBoundingRectangle() const
{
	Rectangle rect0 = m_et0.getBoundingRectangle();
	Rectangle rect1 = m_et1.getBoundingRectangle();

	double min_x = minValue(rect0.getBottomLeft().m_col, rect1.getBottomLeft().m_col);
	double min_y = minValue(rect0.getBottomLeft().m_row, rect1.getBottomLeft().m_row);

	double width = maxValue(rect0.getWidth(), rect1.getWidth());
	double height = rect0.getHeight() + rect1.getHeight();

	return Rectangle(min_x, min_y, width, height);
}

double DoubleArrow::getPerimeter() const
{
	return m_et0.getPerimeter() + m_et1.getPerimeter();
}

double DoubleArrow::getArea() const
{
	return m_et0.getArea() + m_et1.getArea();
}

Vertex DoubleArrow::getCenter() const
{
	Vertex center0 = m_et0.getCenter();
	Vertex center1 = m_et1.getCenter();

	double new_center_x = (center0.m_col + center1.m_col) / 2;
	double new_center_y = (center0.m_row + center1.m_row) / 2;

	return Vertex(new_center_x, new_center_y);
}

bool DoubleArrow::scale(double factor)
{
	Vertex connection_point = getConnection();

	Vertex new_et0_v0 = scalePoint(connection_point, m_et0.getVertex(0), factor);
	Vertex new_et0_v1 = scalePoint(connection_point, m_et0.getVertex(1), factor);
	Vertex new_et0_v2 = scalePoint(connection_point, m_et0.getVertex(2), factor);
	EquilateralTriangle new_et0(new_et0_v0, new_et0_v1, new_et0_v2);

	Vertex new_et1_v0 = scalePoint(connection_point, m_et1.getVertex(0), factor);
	Vertex new_et1_v1 = scalePoint(connection_point, m_et1.getVertex(1), factor);
	Vertex new_et1_v2 = scalePoint(connection_point, m_et1.getVertex(2), factor);
	EquilateralTriangle new_et1(new_et1_v0, new_et1_v1, new_et1_v2);

	if (validDoubleArrow(new_et0, new_et1))
	{
		m_et0 = new_et0;
		m_et1 = new_et1;

		return true;
	}
	return false;
}

bool DoubleArrow::validDoubleArrow(const EquilateralTriangle& et0, const EquilateralTriangle& et1)
{
	bool et0_isUp = triangleIsUp(et0);
	bool et1_isUp = triangleIsUp(et1);

	if (et0_isUp != et1_isUp)
	{
		return false;
	}

	Vertex et0_tip = getTriangleTip(et0);
	Vertex et1_tip = getTriangleTip(et1);

	if (!doubleEqual(et0_tip.m_col, et1_tip.m_col))
	{
		return false;
	}

	double et1_base_height = et1_tip.m_row + (et1_isUp) ? -(et1.getHeight()) : et1.getHeight();

	if (!doubleEqual(et1_base_height, et0_tip.m_row))
	{
		return false;
	}

	return true;

}


Vertex DoubleArrow::getTriangleTip(const EquilateralTriangle& triangle) const
{
	Vertex center = triangle.getCenter();
	Vertex tip;

	if (doubleEqual(triangle.getVertex(0).m_col, center.m_col))
	{
		tip = triangle.getVertex(0);
	}
	else if (doubleEqual(triangle.getVertex(1).m_col, center.m_col))
	{
		tip = triangle.getVertex(1);
	}
	else
	{
		tip = triangle.getVertex(2);
	}

	return tip;
}


bool DoubleArrow::triangleIsUp(const EquilateralTriangle& triangle)
{
	Vertex center = triangle.getCenter();
	Vertex tip = getTriangleTip(triangle);

	return (tip.isHigherThan(center)) ? true : false;
}
