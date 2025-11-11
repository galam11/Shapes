#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <print>

#include "macros.h"
#include "Vertex.h"
#include "Board.h"

#define RECTANGLE            0
#define EQUILATERAL_TRIANGLE 0
#define FRAME                0
#define DOUBLE_ARROW         1

#if RECTANGLE
#include "Rectangle.h"
void printInfo(const Rectangle&);
#endif

#if EQUILATERAL_TRIANGLE
#include "EquilateralTriangle.h"
void printInfo(const EquilateralTriangle&);
#endif

#if FRAME
#include "Frame.h"
void printInfo(const Frame&);
#endif

#if DOUBLE_ARROW
#include "DoubleArrow.h"
void printInfo(const DoubleArrow&);
#endif

void waitForEnter();
Vertex readVertex(std::string_view vertexName, std::string_view shapeName);

template <typename Shape>
void useShape(Shape& shape, std::string_view shapeName);

template <typename Shape>
void draw(const Shape& shape, Board&);

template <typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName);

int main()
{
#if RECTANGLE
    {
        static constexpr auto shapeName = std::string_view("rectangle");

        const auto vertices = std::array<Vertex, 2>
        {
            readVertex("bottom-left", shapeName),
            readVertex("top-right", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto rectangle = Rectangle(vertices.data());
        useShape(rectangle, shapeName);
    }
#endif // RECTANGLE

#if EQUILATERAL_TRIANGLE
    {
        static constexpr auto shapeName = std::string_view("equilateral triangle");

        const auto vertices = std::array<Vertex, 3>
        {
            readVertex("first", shapeName),
            readVertex("second", shapeName),
            readVertex("third", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto equilateralTriangle = EquilateralTriangle(vertices.data());
        useShape(equilateralTriangle, shapeName);
    }
#endif // EQUILATERAL_TRIANGLE

#if FRAME
    {
        static constexpr auto shapeName = std::string_view("frame");

        const auto readRectangle = [&](std::string rectangleName)
        {
            const auto vertices = std::array<Vertex, 2> {
                readVertex(rectangleName + " bottom-left", shapeName),
                readVertex(rectangleName + " top-right", shapeName)
            };
            return Rectangle(vertices.data());
        };

        const auto rectangles = std::array<Rectangle, 2>
        {
            readRectangle("outer"),
            readRectangle("inner")
        };

        std::cin.ignore(); // ignore the enter

        auto frame = Frame(rectangles[0], rectangles[1]);
        useShape(frame, shapeName);
    }
#endif // FRAME

#if DOUBLE_ARROW
    {
        static constexpr auto shapeName = std::string_view("double arrow");

        const auto readTriangle = [&](std::string triangleName) {
            const auto vertices = std::array<Vertex, 3> {
                readVertex(triangleName + " triangle's first", shapeName),
                readVertex(triangleName + " triangle's second", shapeName),
                readVertex(triangleName + " triangle's third", shapeName)
            };
            return EquilateralTriangle(vertices.data());
        };

        const auto triangles = std::array<EquilateralTriangle, 2>
        {
            readTriangle("first"),
            readTriangle("second")
        };

        std::cin.ignore(); // ignore the enter

        auto doubleArrow = DoubleArrow(triangles[0], triangles[1]);
        useShape(doubleArrow, shapeName);
    }
#endif // DOUBLE_ARROW
}

#if RECTANGLE
void printInfo(const Rectangle& rectangle)
{
    static constexpr auto shapeName = std::string_view("rectangle");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::println("The {} vertex of the {} is: {}", vertexName, shapeName, v);
    };

    printVertex(rectangle.getBottomLeft(), "bottom-left");
    printVertex(rectangle.getTopRight(), "top-right");
}
#endif // RECTANGLE

#if EQUILATERAL_TRIANGLE
void printInfo(const EquilateralTriangle& triangle)
{
    static constexpr auto shapeName = std::string_view("equilateral triangle");

    std::println("The vertices of the {} are:", shapeName);
    for (int i = 0; i < 3; ++i)
    {
        std::println("{}", triangle.getVertex(i));
    }

    std::println("The length of the sides of the {} is: {}", shapeName, triangle.getLength());
    std::println("The height of the {} is: {}", shapeName, triangle.getHeight());
}
#endif // EQUILATERAL_TRIANGLE

#if FRAME
void printInfo(const Frame& frame)
{
    static constexpr auto shapeName = std::string_view("frame");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::println("The {} vertex of the {} is: {}", vertexName, shapeName, v);
    };

    printVertex(frame.getBottomLeft(), "bottom-left");
    printVertex(frame.getTopRight(), "top-right");

    std::println("The thickness of the {} is: {}", shapeName, frame.getThickness());
}
#endif // FRAME

#if DOUBLE_ARROW
void printInfo(const DoubleArrow& doubleArrow)
{
    static constexpr auto shapeName = std::string_view("double arrow");

    std::println("The lengths of the triangles of the {} are:", shapeName);
    for (int i = 0; i < 2; ++i)
    {
        std::println("Triangle {}: {}", i + 1, doubleArrow.getLength(i));
    }

    std::println("The heights of the triangles of the {} are:", shapeName);
    for (int i = 0; i < 2; ++i)
    {
        std::println("Triangle {}: {}", i + 1, doubleArrow.getHeight(i));
    }

    std::println("The connection point of the {} is: {}", shapeName, doubleArrow.getConnection());
}
#endif // DOUBLE_ARROW

void waitForEnter()
{
    std::println("Press Enter to continue...");
    auto line = std::string();
    std::getline(std::cin, line);
}

Vertex readVertex(std::string_view vertexName, std::string_view shapeName)
{
    std::println("Please enter x and y coordinates for the {} vertex of the {}:",
        vertexName, shapeName);
    auto v = Vertex();
    std::cin >> v;
    return v;
}

template<typename Shape>
void useShape(Shape& shape, std::string_view shapeName)
{
    auto board = Board();
    auto print = [&]
    {
        draw(shape, board);
        printInfo(shape);
        printGenericInfo(shape, shapeName);
        waitForEnter();
    };

    print();

    board.clear();
    std::cout << "Now scaled by factor of 2:\n\n";
    if (shape.scale(2))
    {
        print();
    }
    else
    {
        std::cout << "Scaling failed!\n";
        waitForEnter();
    }
}

template<typename Shape>
void draw(const Shape& shape, Board& board)
{
    shape.draw(board);
    board.print();
    waitForEnter();

    std::println("Now with the bounding rectangle:");
    auto boundingRect = shape.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();
}

template<typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName)
{
    std::println("The perimeter of the {} is: {}",
        shapeName, shape.getPerimeter());

    std::println("The area of the {} is: {}",
        shapeName, shape.getArea());

    std::println("The center of the {} is: {}",
        shapeName, shape.getCenter());
}
