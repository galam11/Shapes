#include "DoubleArrow.h"
#include "Board.h"
#include "Vertex.h"
#include "Rectangle.h"
#include "EquilateralTriangle.h"
#include <cmath>
#include "macros.h"

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
//
//DoubleArrow::DoubleArrow (const EquilateralTriangle& first, double length)
//{
//	
//}


double DoubleArrow::getLength(double index) const
{
	
}

//double DoubleArrow::getHeight(double index) const
//{
//	
//}
//
//Vertex DoubleArrow::getConnection() const
//{
//	
//}
//
//
//void DoubleArrow::draw(Board& board) const
//{
//	
//}
//
//Rectangle DoubleArrow::getBoundingRectangle() const
//{
//	
//}
//
//double DoubleArrow::getPerimeter() const
//{
//	
//}
//
//double DoubleArrow::getArea() const
//{
//	
//}
//
//Vertex DoubleArrow::getCenter() const
//{
//	
//}
//
//bool DoubleArrow::scale(double factor)
//{
//	
//}

bool DoubleArrow::validDoubleArrow(const EquilateralTriangle& et0, const EquilateralTriangle& et1)
{
	return true;
}