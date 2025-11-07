#include "Frame.h"

#include "Vertex.h"
#include "Utilities.h"

Frame::Frame(const Rectangle& outer, const Rectangle& inner)
{
	if (validFrame(outer, inner))
    {
    	m_outer = outer;
        m_inner = inner;
    }
}

Frame::Frame(const Rectangle& outer, double thickness) :
	Frame(
		outer,
		Rectangle (
			outer.getCenter(),
			outer.getWidth() - 2 * thickness,
			outer.getHeight() - 2 * thickness
		)
	) { }


Vertex Frame::getBottomLeft() const
{
	return m_outer.getBottomLeft();
}

Vertex Frame::getTopRight() const
{
	return m_outer.getTopRight();
}

double Frame::getThickness() const
{
	return (m_outer.getWidth() - m_outer.getWidth()) / 2;
}


void Frame::draw(Board& board) const
{
	m_inner.draw(board);
    m_outer.draw(board);
}

Rectangle Frame::getBoundingRectangle() const
{
	return m_outer;
}

double Frame::getPerimeter() const
{
	return m_inner.getPerimeter() + m_outer.getPerimeter();
}

double Frame::getArea() const
{
	return m_outer.getArea() - m_inner.getArea();
}

Vertex Frame::getCenter() const
{
	return m_outer.getCenter();
}

bool Frame::scale(double factor)
{
	if (m_outer.scale(factor))
    {
    	m_inner.scale(factor);
        return true;
    }
    return false;
}

bool validFrame(Rectangle outer, Rectangle inner)
{
	double widthDiff = outer.getWidth() - inner.getWidth();
    double hightDiff = outer.getHeight() - inner.getHeight();

    Vertex centerOuter = outer.getCenter();
	Vertex centerInner = inner.getCenter();

    return widthDiff >= 0
           && doubleEqual(widthDiff, hightDiff)
           && doubleEqual(centerOuter.m_col,centerInner.m_col)
           && doubleEqual(centerOuter.m_row, centerInner.m_row);
}

