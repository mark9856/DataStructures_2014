#include <vector>
#include <iostream>

class Triangle{
    public:
        // CONSTRUCTOR
        Triangle(double l1, double l2, double l3);
        Triangle(std::vector <double> vec);

        // ACCESSOR
        double getPerimeter() const;
        double getArea() const;

        // MODIFITER
        void doubleShortestEdge();

    private:
        double a;
        double b;
        double c;
};
