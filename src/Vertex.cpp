#include "Vertex.h"
#include "macros.h"

#include <iostream>

#include "Utilities.h"

bool Vertex::isHigherThan(const Vertex& other) const
{
    return m_row > other.m_row;
}

bool Vertex::isToTheRightOf(const Vertex& other) const
{
    return m_col > other.m_col;
}

bool Vertex::isValid() const
{
    return m_col >= 0 && m_col <= MAX_COL && m_row >= 0 && m_row <= MAX_ROW;
}

std::istream& operator>>(std::istream& istr, Vertex& v)
{
    return istr >> v.m_col >> v.m_row;
}

std::ostream& operator<<(std::ostream& ostr, const Vertex& v)
{
    return ostr << "(" << v.m_col << ", " << v.m_row << ")";
}


//vertex utility functions
//scales a point by a given factor
Vertex scalePoint(const Vertex& center, const Vertex& point, double factor)
{
    return Vertex
    (
        center.m_col + (point.m_col - center.m_col) * factor,
        center.m_row + (point.m_row - center.m_row) * factor
    );
}



