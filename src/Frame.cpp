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

// constracts the inner rect using the outer center
// and subtracting 2 times the thickness from the width and hight
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
    //botom left same as the outter rect
	return m_outer.getBottomLeft();
}

Vertex Frame::getTopRight() const
{
    //top right same as outter rect
	return m_outer.getTopRight();
}

double Frame::getThickness() const
{
    // the outer width is two time the inner width + thickness,
    // so we can calculat the thickness like so
	return (m_outer.getWidth() - m_outer.getWidth()) / 2;
}


void Frame::draw(Board& board) const
{
    //draw the two frames
	m_inner.draw(board);
    m_outer.draw(board);
}

Rectangle Frame::getBoundingRectangle() const
{
    // the frames bounding box is the same as the outter rect
	return m_outer;
}

double Frame::getPerimeter() const
{
    // the sum of the rects perimeter
	return m_inner.getPerimeter() + m_outer.getPerimeter();
}

double Frame::getArea() const
{
    // the diffrenc between the area of the outter rect to the inner
	return m_outer.getArea() - m_inner.getArea();
}

Vertex Frame::getCenter() const
{
    // the center of the frame is the same of one of the frames
	return m_outer.getCenter();
}

bool Frame::scale(double factor)
{
    // cheking if the scail of the outer succeeded
    // if the outer one Succeeded then the smaller one will succseed as well
	if (m_outer.scale(factor))
    {
        // then scailing the inner one
    	m_inner.scale(factor);
        return true;
    }
    // faild to scail so return false
    return false;
}

bool Frame::validFrame(Rectangle outer, Rectangle inner)
{
	double widthDiff = outer.getWidth() - inner.getWidth();
    double hightDiff = outer.getHeight() - inner.getHeight();

    Vertex centerOuter = outer.getCenter();
	Vertex centerInner = inner.getCenter();

    // cheks if diff between the widths and the hights of the rect are same
    // and if the diff it self is grater or equal to zero
    // and if both rects have the same points
    return widthDiff >= 0
           && doubleEqual(widthDiff, hightDiff)
           && doubleEqual(centerOuter.m_col,centerInner.m_col)
           && doubleEqual(centerOuter.m_row, centerInner.m_row);
}