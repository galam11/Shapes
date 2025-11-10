#include "DoubleArrow.h"
#include "Board.h"
#include "Vertex.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"
#include <cmath>
#include "macros.h"
#include "Utilities.h"

// Constructors
DoubleArrow::DoubleArrow (const EquilateralTriangle& first, const EquilateralTriangle& second)
{
	setTriangles(first, second);
}

DoubleArrow::DoubleArrow (const EquilateralTriangle& first, double length)
{
	Vertex first_triangle_tip = getTriangleTip(first);

	Vertex second_triangle_left(first_triangle_tip.m_col - (length / 2), first_triangle_tip.m_row);
	Vertex second_triangle_right(first_triangle_tip.m_col + (length / 2), first_triangle_tip.m_row);

	double second_triangle_height = TRIANGLE_HEIGHT_COEFFICIENT * length;
	double second_triangle_tip_y = first_triangle_tip.m_row;
	second_triangle_tip_y += (triangleIsUp(first) ? 1 : -1) * second_triangle_height;
	Vertex second_triangle_tip(first_triangle_tip.m_col, second_triangle_tip_y);

	EquilateralTriangle second(second_triangle_left, second_triangle_right, second_triangle_tip);

	setTriangles(first, second);
}

// DoubleArrow only functions
double DoubleArrow::getLength(int index) const
{
	return (index == 0) ? m_triangle0.getLength() : m_triangle1.getLength();
}

double DoubleArrow::getHeight(int index) const
{
	return (index == 0) ? m_triangle0.getHeight() : m_triangle1.getHeight();
}

Vertex DoubleArrow::getConnection() const
{
	return getTriangleTip(m_triangle0);
}

// All shapes functions

void DoubleArrow::draw(Board& board) const
{
	m_triangle0.draw(board);
	m_triangle1.draw(board);
}

Rectangle DoubleArrow::getBoundingRectangle() const
{
	Rectangle rect0 = m_triangle0.getBoundingRectangle();
	Rectangle rect1 = m_triangle1.getBoundingRectangle();

	double min_x = minValue(rect0.getBottomLeft().m_col, rect1.getBottomLeft().m_col);
	double min_y = minValue(rect0.getBottomLeft().m_row, rect1.getBottomLeft().m_row);

	double width = maxValue(rect0.getWidth(), rect1.getWidth());
	double height = rect0.getHeight() + rect1.getHeight();

	return Rectangle(min_x, min_y, width, height);
}

double DoubleArrow::getPerimeter() const
{
	return m_triangle0.getPerimeter() + m_triangle1.getPerimeter();
}

double DoubleArrow::getArea() const
{
	return m_triangle0.getArea() + m_triangle1.getArea();
}

Vertex DoubleArrow::getCenter() const
{
	Vertex center0 = m_triangle0.getCenter();
	Vertex center1 = m_triangle1.getCenter();

	double new_center_x = (center0.m_col + center1.m_col) / 2;
	double new_center_y = (center0.m_row + center1.m_row) / 2;

	return Vertex(new_center_x, new_center_y);
}

bool DoubleArrow::scale(double factor)
{
	Vertex connection_point = getConnection();

	Vertex new_triangle0_v0 = scalePoint(connection_point, m_triangle0.getVertex(0), factor);
	Vertex new_triangle0_v1 = scalePoint(connection_point, m_triangle0.getVertex(1), factor);
	Vertex new_triangle0_v2 = scalePoint(connection_point, m_triangle0.getVertex(2), factor);
	EquilateralTriangle new_triangle0(new_triangle0_v0, new_triangle0_v1, new_triangle0_v2);

	Vertex new_triangle1_v0 = scalePoint(connection_point, m_triangle1.getVertex(0), factor);
	Vertex new_triangle1_v1 = scalePoint(connection_point, m_triangle1.getVertex(1), factor);
	Vertex new_triangle1_v2 = scalePoint(connection_point, m_triangle1.getVertex(2), factor);
	EquilateralTriangle new_triangle1(new_triangle1_v0, new_triangle1_v1, new_triangle1_v2);

	return setTriangles(new_triangle0, new_triangle1);
}

bool DoubleArrow::validDoubleArrow(const EquilateralTriangle& triangle0, const EquilateralTriangle& triangle1)
{
	bool triangle0_isUp = triangleIsUp(triangle0);
	bool triangle1_isUp = triangleIsUp(triangle1);

	if (triangle0_isUp != triangle1_isUp)
	{
		return false;
	}

	Vertex triangle0_tip = getTriangleTip(triangle0);
	Vertex triangle1_tip = getTriangleTip(triangle1);

	if (!doubleEqual(triangle0_tip.m_col, triangle1_tip.m_col))
	{
		return false;
	}

	double triangle1_base_height = triangle1_tip.m_row;
	triangle1_base_height += (triangle1_isUp ? -1 : 1) * triangle1.getHeight();

	if (!doubleEqual(triangle1_base_height, triangle0_tip.m_row))
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

	return tip.isHigherThan(center);
}

bool DoubleArrow::setTriangles(const EquilateralTriangle& triangle0, const EquilateralTriangle& triangle1)
{
	if (validDoubleArrow(triangle0, triangle1))
	{
		m_triangle0 = triangle0;
		m_triangle1 = triangle1;

		return true;
	}
	return false;
}