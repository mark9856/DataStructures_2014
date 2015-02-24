#include <iostream>
#include <vector>

#include "Rectangle.h"
#include "Point2D.h"

int main(){
    Point2D a(9.0, 9.0);
    Point2D b(1.0, 1.0);
    Point2D c(2.0, 10.0);
    Point2D d(3.0, 8.0);
    Point2D e(10.0, 5.0);
    Point2D f(5.0, 5.0);
    Rectangle r1(b, a);
    std::cout << "whether c is within r1 " << r1.is_point_within(c) << std::endl;
    std::cout << "whether d is within r1 " << r1.is_point_within(d) << std::endl;
    // r1.is_point_within(c);
    // r1.is_point_within(d);
    Point2D r1r = r1.upper_right_corner();
    Point2D r1l = r1.lower_left_corner();

    std::cout << "add e " << r1.add_point(e) << std::endl;
    std::cout << "add f " << r1.add_point(f) << std::endl;
    std::vector <Point2D> r1PointsContained = r1.points_contained();
    
    return 0;
}
