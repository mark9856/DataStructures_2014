#include <iostream>
#include <vector>
#include <cmath>

#include "triangle.h"

Triangle::Triangle(double l1, double l2, double l3){
    a = l1;
    b = l2;
    c = l3;
}

Triangle::Triangle(std::vector <double> vec){
    a = vec[0];
    b = vec[1];
    c = vec[2];
}

double Triangle::getPerimeter() const{
    return a + b + c;
}

double Triangle::getArea() const{
    double s = (a + b + c)/2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

void Triangle::doubleShortestEdge(){
    if(a >= b){
        if (b >= c){
            c = 2*c;
        }
        else b = 2*b;
    }
    else{
        if(c <= a){
            c = 2*c;
        }
        else a = 2*a;
    }
}
