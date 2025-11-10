#pragma once

#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"

class EquilateralTriangle {

private: // Private members
	Vertex m_v0 = Vertex(20, 20);
	Vertex m_v1 = Vertex(30, 20);
	Vertex m_v2 = Vertex(25, 20 + DEFAULT_COEFFICIENT);

public:

	// Constructors
	EquilateralTriangle(const Vertex vertices[3]);
	EquilateralTriangle(Vertex v0, Vertex v1, Vertex v2);
	EquilateralTriangle(Vertex v, double length, bool isUp);

	// EquilateralTriangle only functions
	Vertex getVertex(int index) const;
	double getLength() const;
	double getHeight() const;

	// All shapes functions
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getPerimeter() const;
	double getArea() const;
	Vertex getCenter() const;
	bool scale(double factor);

	// Private utility functions
private:
	bool validEquilateralTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	bool setVertices(Vertex& v0, Vertex& v1, Vertex& v2);
};