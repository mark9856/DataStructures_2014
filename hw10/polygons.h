#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include "utilities.h"

#ifndef __player_h_
#define __player_h_

// To identify what kind of shape is it
bool isPolygon(std::vector<Point>& points);
bool isTriangle(std::vector<Point>& points);
bool isIsoscelesTriangle(std::vector<Point>& points);
bool isRightTriangle(std::vector<Point>& points);
bool isObtuseTriangle(std::vector<Point>& points);
bool isIsoscelesObtuseTriangle(std::vector<Point>& points);
bool isIsoscelesRightTriangle(std::vector<Point>& points);
bool isEquilateralTriangle(std::vector<Point>& points);
bool isQuadrilateral(std::vector<Point>& points);
bool isTrapezoid(std::vector<Point>& points);
bool isKite(std::vector<Point>& points);
bool isParallelogram(std::vector<Point>& points);
bool isArrow(std::vector<Point>& points);
bool isIsoscelesTrapezoid(std::vector<Point>& points);
bool isRhombus(std::vector<Point>& points);
bool isRectangle(std::vector<Point>& points);
bool isSquare(std::vector<Point>& points);

// to get all of the angles in this shape
void getAngles(std::vector<Point> points, std::vector<double> &angles);
// to get all of the sides in this shape
void getSides(std::vector<Point> points, std::vector<Vector> & v);

// it will fail if there is not points
class Polygon{
    public:
        Polygon(){}
        Polygon(const std::string n, const std::vector<Point> points)throw(int){
            if(points.size() <= 0) throw 1;
            name = n;
            verts = points;
        }
        std::string getName(){return name;}
        bool HasAllEqualSides();
        bool HasAllEqualAngles();
        bool HasARightAngle();
        bool HasAnObtuseAngle();
        bool HasAnAcuteAngle();
        bool IsConvex();
        bool IsConcave();
        virtual ~Polygon(){}
    protected:
        std::string name;
        std::vector<Point> verts;
};

// it will fail if there is any sides are Parallel
class Triangle: public Polygon{
    public:
        Triangle(){}
        Triangle(std::string n, std::vector<Point> points) throw(int){
            if(!isTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will fail if no two sides are EqualSides
class IsoscelesTriangle: virtual public Triangle{
    public:
        IsoscelesTriangle(){}
        IsoscelesTriangle(std::string n, std::vector<Point> points) throw(int):Triangle(){
            if(!isIsoscelesTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will fail if there is not RightAngle
class RightTriangle: virtual public Triangle{
    public:
        RightTriangle(){}
        RightTriangle(std::string n, std::vector<Point> points) throw(int):Triangle(){
            if(!isRightTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
        
};

// it will fail if there is not ObtuseAngle
class ObtuseTriangle: virtual public Triangle{
    public:
        ObtuseTriangle(){}
        ObtuseTriangle(std::string n, std::vector<Point> points) throw(int):Triangle(){
            if(!isObtuseTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will fail if not all sides EqualSides
class EquilateralTriangle: public IsoscelesTriangle{
    public:
        EquilateralTriangle(){}
        EquilateralTriangle(std::string n, std::vector<Point> points) throw(int){
            if(!isEquilateralTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will fail if it is not IsoscelesTriangle and RightTriangle
class IsoscelesRightTriangle: public RightTriangle, public IsoscelesTriangle{
    public:
        IsoscelesRightTriangle(){}
        IsoscelesRightTriangle(std::string n, std::vector<Point> points) throw(int):RightTriangle(), IsoscelesTriangle(),Triangle(){
            if(!isIsoscelesRightTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will fail if it is not IsoscelesTriangle and ObtuseTriangle
class IsoscelesObtuseTriangle: public IsoscelesTriangle, public ObtuseTriangle{
    public:
        IsoscelesObtuseTriangle(){}
        IsoscelesObtuseTriangle(std::string n, std::vector<Point> points) throw(int): IsoscelesTriangle(), ObtuseTriangle(), Triangle(){
            if(!isIsoscelesObtuseTriangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if there are 4 sides and not angles equal to 0 or 180
class Quadrilateral: public Polygon{
    public:
        Quadrilateral(){}
        Quadrilateral(std::string n, std::vector<Point> points) throw(int){
            if(!isQuadrilateral(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if any pair of sides are Parallel
class Trapezoid: virtual public Quadrilateral{
    public:
        Trapezoid(){}
        Trapezoid(std::string n, std::vector<Point> points) throw(int):Quadrilateral(){
            if(!isTrapezoid(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if there it's concave
class Arrow: public Quadrilateral{
    public:
        Arrow(){}
        Arrow(std::string n, std::vector<Point> points) throw(int){
            if(!isArrow(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if there are 2 pair of sides Parallel
class Parallelogram: virtual public Trapezoid{
    public:
        Parallelogram(){}
        Parallelogram(std::string n, std::vector<Point> points) throw(int):Trapezoid(){
            if(!isParallelogram(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if there are 2 near sides EqualSides
class Kite: virtual public Quadrilateral{
    public:
        Kite(){}
        Kite(std::string n, std::vector<Point> points) throw(int):Quadrilateral(){
            if(!isKite(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if it's IsoscelesTrapezoid
class IsoscelesTrapezoid: virtual public Trapezoid{
    public:
        IsoscelesTrapezoid(){}
        IsoscelesTrapezoid(std::string n, std::vector<Point> points) throw(int): Trapezoid(), Quadrilateral(){
            if(!isIsoscelesTrapezoid(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if it's Parallelogram and Kite
class Rhombus: virtual public Parallelogram, public Kite{
    public:
        Rhombus(){}
        Rhombus(std::string n, std::vector<Point> points) throw(int):Kite(), Parallelogram(), Quadrilateral(){
            if(!isRhombus(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if it's Parallelogram and IsoscelesTrapezoid
class Rectangle: virtual public IsoscelesTrapezoid, public Parallelogram{
    public:
        Rectangle(){}
        Rectangle(std::string n, std::vector<Point> points) throw(int):IsoscelesTrapezoid(), Parallelogram(), Trapezoid() {
            if(!isRectangle(points)) throw -1;
            name = n;
            verts = points;
        }
};

// it will success if it's Rhombus and Rectangle
class Square: public Rectangle, public Rhombus{
    public:
        Square(){}
        Square(std::string n, std::vector<Point> points) throw(int):Rectangle(), Rhombus(), Parallelogram(){
            if(!isSquare(points)) throw -1;
            name = n;
            verts = points;
        }
};


#endif
