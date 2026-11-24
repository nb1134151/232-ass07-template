#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

// ============================================================
// PART 1 Tests: Shapes
// ============================================================

/// Create Circle(1), Square(2), Rectangle(2, 3).
/// Verify area() is pi, 4 and 6 (compare doubles with std::fabs(a - b) < 1e-9).
void test_shape_areas(void)
{
    Circle circle(1);
    Square square(2);
    Rectangle rectangle(2, 3);
    double area = circle.area();

    TEST_ASSERT_TRUE_MESSAGE(std::fabs(area - std::numbers::pi) < 1e-9, "Error: circle.area() is not equal to pi");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(square.area() - 4.0) < 1e-9, "Error: square.area() is not equal to 4");
    TEST_ASSERT_TRUE_MESSAGE(std::fabs(rectangle.area() - 6.0) < 1e-9, "Error: rectangle.area() is not equal to 6");

}

/// Create an array of three Shape* (a Circle, a Square, a Rectangle) with new.
/// Verify name() through the BASE pointer gives "Circle", "Square", "Rectangle".
/// Delete the shapes through the base pointers.
void test_shape_names_through_base_pointer(void)
{
    Shape *shapes[] = {new Circle(1), new Square(2), new Rectangle(2, 3)};

    TEST_ASSERT_TRUE_MESSAGE(shapes[0]->name() == "Circle", "Error: first name is not Circle");
    TEST_ASSERT_TRUE_MESSAGE(shapes[1]->name() == "Square", "Error: second name is not Square");
    TEST_ASSERT_TRUE_MESSAGE(shapes[2]->name() == "Rectangle", "Error: third name is not Rectangle");

    for (Shape *shape: shapes) {
        delete shape;
    }
}

/// Create Square(1) and Square(2). Take two const Shape& to them.
/// Verify small < big is true, big < small is false, small < small is false.
void test_shape_operator_less(void)
{
    Square square1(1);
    Square square2(2);

    Shape& ss = square1;
    Shape& sb = square2;

    
    TEST_ASSERT_TRUE_MESSAGE(ss < sb == true, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(sb < sb == false, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(ss < ss == false, "TODO: Implement this test");

}

/// Create Square(2) and Rectangle(1, 4): both have area 4.
/// Verify that NEITHER a < b NOR b < a is true.
void test_shape_equal_area_not_less(void)
{
    Square square1(2);
    Rectangle rectangle1(1, 4);

    Shape& s = square1;
    Shape& r = rectangle1;

    TEST_ASSERT_TRUE_MESSAGE(s < r == false, "Error");
    TEST_ASSERT_TRUE_MESSAGE(r < s == false, "TODO: Implement this test");

}

// ============================================================
// PART 2 Tests: ShapeList
// ============================================================

/// Create a ShapeList. Add new Circle(1) and new Square(2) with addShape.
/// Verify both calls return 0 and length() is 2.
/// (Do NOT delete the shapes yourself: the list owns them.)
void test_list_add_and_length(void)
{
    ShapeList sl;
    int result = sl.addShape(new Circle(1));
    int result2 = sl.addShape(new Square(2));



    TEST_ASSERT_TRUE_MESSAGE(result == 0 && result2 == 0, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(result == 0 && result2 == 0, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(sl.length() == 2, "TODO: Implement this test");

}

/// Create a ShapeList. Call addShape(nullptr).
/// Verify it returns -1 and length() stays 0.
void test_list_add_null_guard(void)
{
    ShapeList sl;
    int result = sl.addShape(nullptr);

    TEST_ASSERT_TRUE_MESSAGE(result == -1, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(sl.length() == 0, "TODO: Implement this test");
}

/// Add Rectangle(2, 5) (area 10), Circle(1) (area 3.14), Square(2) (area 4).
/// Call insertionSort(). Verify nameAt(0), nameAt(1), nameAt(2) are
/// "Circle", "Square", "Rectangle" and isSorted() is true.
void test_insertionSort_orders_by_area(void)
{
    ShapeList sl;

    sl.addShape(new Rectangle(2, 5));
    sl.addShape(new Circle(1));
    sl.addShape(new Square(2));

    sl.insertionSort();


    TEST_ASSERT_TRUE_MESSAGE(sl.nameAt(0) == "Circle", "Error: nameAt(0) name is not Circle");
    TEST_ASSERT_TRUE_MESSAGE(sl.nameAt(1) == "Square", "Error: nameAt(1) name is not Square");
    TEST_ASSERT_TRUE_MESSAGE(sl.nameAt(2) == "Rectangle", "Error: nameAt(2) name is not Rectangle");

    TEST_ASSERT_TRUE_MESSAGE(sl.isSorted() == true, "TODO: Implement this test");

}

/// Call insertionSort() on an EMPTY list: no crash, length() is 0.
/// Then add ONE shape and sort again: length() is 1 and nameAt(0) is unchanged.
void test_insertionSort_empty_and_single(void)
{
    ShapeList sl;
    sl.insertionSort();

    int prev_len = sl.length();
    sl.addShape(new Square(2));

    TEST_ASSERT_TRUE_MESSAGE(prev_len == 0, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(sl.length() == 1, "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(sl.nameAt(0) == "Square", "TODO: Implement this test");


}
