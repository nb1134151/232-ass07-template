// ============================================================
// CSCI 232 Assignment 07 – Shapes, Polymorphism and Insertion Sort
// Student Implementation
// ============================================================

#include "code.hpp"
#include <iostream>
#include <iterator>
#include <numbers>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Nick Badovinac";
 std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
 "assignment independently, except where explicitly noted and referenced. "
 "Any collaboration or use of external resources has been properly cited. "
 "I am fully aware of the consequences of academic dishonesty and agree "
 "to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Shape, Circle, Square, Rectangle
// ============================================================

/// True if THIS shape has a strictly smaller area() than other.
bool Shape::operator<(const Shape &other) const
{
    if (this->area() < other.area()) {
        return true;
    }
    return false;
}

/// Constructor with a member initializer list.
Circle::Circle(double newRadius)
: radius(newRadius)
{
    // TODO: move the initialization of 'radius' into an initializer list
}

/// pi * radius * radius, use std::numbers::pi
double Circle::area() const
{
    double area = std::numbers::pi * radius * radius;
    
    return area;
}

/// Return exactly "Circle".
std::string Circle::name() const
{
    
    return "Circle";
}

Square::Square(double newSide)
: side(newSide)
{
}

/// side * side
double Square::area() const
{
    double area = side * side;
    return area;
}

/// Return exactly "Square".
std::string Square::name() const
{
    return "Square";
}

Rectangle::Rectangle(double newWidth, double newHeight)
: width(newWidth), height(newHeight)
{
    // TODO: initializer list
}

/// width * height
double Rectangle::area() const
{
    double area = width * height;
    return area;
}

/// Return exactly "Rectangle".
std::string Rectangle::name() const
{
    // TODO: implement
    return "Rectangle";
}

// ============================================================
// PART 2: ShapeList
// ============================================================

/// RAII: delete EVERY shape, then clear the list.
ShapeList::~ShapeList()
{
    for (Shape *shape: data) { 
        delete shape;
    }
}

/// Append at the end. Return -1 if newShapePtr is nullptr, 0 on success.
int ShapeList::addShape(Shape *newShapePtr)
{
    if (newShapePtr == nullptr) {
        return -1;
    }

    data.push_back(newShapePtr);

    return 0;
}

/// Delete the first shape and remove it from the list.
/// Return false if the list is empty, true otherwise.
bool ShapeList::removeFirst()
{
    if(data.empty() == true) {
        return false;
    }

    Shape *front = data.front();

    data.pop_front();

    delete front;


    return true;
}

/// Number of shapes in the list.
int ShapeList::length() const
{
    int size = data.size();

    return size;
}

/// Sum of area() of all shapes (0.0 if empty).
double ShapeList::totalArea() const
{
    double area = 0.0;

    if (data.empty() == true) {
        return area;
    }

    for (Shape *shape : data) {
        
        area = area + shape->area();
    }

    return area;
}

/// One line per shape: name, one space, area. Return the number of shapes.
int ShapeList::printList() const
{
    for (Shape *shape : data) {
        std::cout << shape->name() << " " << shape->area() << "\n"; 
    }
    return data.size();
}

/// area() of the shape at index, or std::nullopt if index is out of range.
/// Hint: std::next(data.begin(), index)
std::optional<double> ShapeList::areaAt(int index) const
{
    if (index < 0 || index >= data.size()) {
        return std::nullopt;
    }

    Shape *shape = *std::next(data.begin(), index);
    

    return shape->area();
}

/// name() of the shape at index, or std::nullopt if index is out of range.
std::optional<std::string> ShapeList::nameAt(int index) const
{
    if (index < 0 || index >= data.size()) {
        return std::nullopt;
    }

    Shape *shape = * std::next(data.begin(), index);

    if (shape == nullptr) {
        return std::nullopt;
    }

    return shape->name();
}

/// Your own STABLE insertion sort, smallest area first.
/// Compare shapes with operator< (dereference the pointers!).
/// Hint: for every element, walk left while the previous shape is bigger,
/// then move the element there with data.splice(...).
void ShapeList::insertionSort()
{
    if (data.size() < 2 || (data.empty())) {
        return;
    }

    auto current = std::next(data.begin()); // 2nd element of data

    while (current != data.end()) {
        auto next = std::next(current); // element after current
        auto position = current;
        

        while(position != data.begin() && (**current) < (**std::prev(position))) { // walk back until position is either at the beginning of the list, or a m
                                                                                  //  element smaller than the current one to sort is found.
            --position;
        }

        if(position != current) { // check if any move was made in the first place.
            data.splice(position, data, current);
        }
        current = next;
    }
}

/// True if no shape is smaller than the one before it.
bool ShapeList::isSorted() const
{
    if (data.empty()) {
        return true;
    }

    Shape *prev = data.front();

    for (Shape *shape : data) {
        if(shape->area() < prev->area()) {
            return false;
        }
        prev = shape;
    }
    return true;
}
