#include <cmath>
#include <cassert>
#include <vector>
#include <list>
#include "polygons.h"

bool Polygon::HasAllEqualSides() {
    /*
    if(points.size() == 3){
        std::vector<double> sVectors;
        for(int i = 0; i < points.size(); ++ i){
            for(int j = i + 1; j < points.size(); ++ j){
                double v = DistanceBetween(points[i], points[j]);
                sVectors.push_back(v);
            }
        }
        bool found = false;
        for(int i = 0; i < sVectors.size(); ++ i){
            for(int j = i + 1; j < sVectors.size(); ++ j){
                if(!EqualSides(sVectors[i], sVectors[j])){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
            return true;
        }
        else return false;
    }
    return false;
    */
    // get all the sides and then make sure all the sides are equal
    int numPoints = verts.size();
    int numSides = numPoints * (numPoints - 1) / 2;
    std::vector<double> sides;
    for(int i = 0; i < numPoints - 1; ++ i){
        sides.push_back(DistanceBetween(verts[i], verts[i + 1]));
    }
    sides.push_back(DistanceBetween(verts[numPoints - 1], verts[0]));
    for(int i = 1; i < sides.size(); ++ i){
        if(!EqualSides(sides[i], sides[0])) return false;
    }
    return true;
}

// get all the angles in this shape
void getAngles(std::vector<Point> points, std::vector<double>& angles){
    for(int i = 0; i < points.size() - 2; ++ i){
        double a = Angle(points[i], points[i + 1], points[i + 2]);
        angles.push_back(a);
    }
    angles.push_back(Angle(points[points.size() - 2], points[points.size() - 1],points[0]));
    angles.push_back(Angle(points[points.size() - 1], points[0], points[1]));
}

bool Polygon::HasAllEqualAngles(){
    /*
    if(points.size() == 3){
        std::vector<double> sAngles;
        for(int i = 0; i < points.size(); ++ i){
            for(int j = i + 1; j < points.size(); ++ j){
                for(int k = j + 1; k < points.size(); ++ k){
                    double a = Angle(points[i], points[j], points[k]);
                    if(ReflexAngle(a)){
                        a = 360.0 - a;
                    }
                    sAngles.push_back(a);
                }
            }
        }
        bool found = false;
        for(int i = 0; i < sAngles.size(); ++ i){
            for(int j = 0; j < sAngles.size(); ++ j){
                if(!EqualAngles(sAngles[i], sAngles[j])){
                    found = true;
                    break;
                }
            }
        }
        if(found){
            return true;
        }
        else return false;
    }
    return false;
    */
    // get all the angles then compare all the angles
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(!EqualAngles(angles[i], angles[0])) return false;
    }
    return true;
}

bool Polygon::HasARightAngle() {
    /*
    if(points.size() == 3){
        std::vector<double> sAngles;
        for(int i = 0; i < points.size(); ++ i){
            for(int j = i + 1; j < points.size(); ++ j){
                for(int k = j + 1; k < points.size(); ++ k){
                    double a = Angle(points[i], points[j], points[k]);
                    if(ReflexAngle(a)){
                        a = 360.0 - a;
                    }
                    sAngles.push_back(a);
                }
            }
        }
        bool found = false;
        for(int i = 0; i < sAngles.size(); ++ i){
            if(RightAngle(sAngles[i])){
                found = true;
                break;
            }
        }
        if(found){
            return true;
        }
        else return false;
    }
    return false;
    */
    // get all the angles and find out is there any right angle
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(RightAngle(angles[i])) return true;
    }
    return false;
}

bool Polygon::HasAnObtuseAngle(){
    /*
    if(points.size() == 3){
        std::vector<double> sAngles;
        for(int i = 0; i < points.size(); ++ i){
            for(int j = i + 1; j < points.size(); ++ j){
                for(int k = j + 1; k < points.size(); ++ k){
                    double a = Angle(points[i], points[j], points[k]);
                    if(ReflexAngle(a)){
                        a = 360.0 - a;
                    }
                    sAngles.push_back(a);
                }
            }
        }
        bool found = false;
        for(int i = 0; i < sAngles.size(); ++ i){
            if(ObtuseAngle(sAngles[i])){
                found = true;
                break;
            }
        }
        if(found){
            return true;
        }
        else return false;
    }
    return false;
    */
    // get all the angles and find out is there any obtuse angle
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(ObtuseAngle(angles[i])) return true;
    }
    return false;
}
bool Polygon::HasAnAcuteAngle(){
    /*
    if(points.size() == 3){
        std::vector<double> sAngles;
        for(int i = 0; i < points.size(); ++ i){
            for(int j = i + 1; j < points.size(); ++ j){
                for(int k = j + 1; k < points.size(); ++ k){
                    double a = Angle(points[i], points[j], points[k]);
                    if(ReflexAngle(a)){
                        a = 360.0 - a;
                    }
                    sAngles.push_back(a);
                }
            }
        }
        bool found = false;
        for(int i = 0; i < sAngles.size(); ++ i){
            if(AcuteAngle(sAngles[i])){
                found = true;
                break;
            }
        }
        if(found){
            return true;
        }
        else return false;
    }
    return false;
    */
    // get all the angles and find out is there any acute angle
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(AcuteAngle(angles[i])) return true;
    }
    return false;
}
bool Polygon::IsConvex(){
    // get all the angles and find out is there any ReflexAngle
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(ReflexAngle(angles[i])) return false;
    }
    return true;
}
bool Polygon::IsConcave(){
    // get all the angles and find out is there any ReflexAngle
    std::vector<double> angles;
    getAngles(verts, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(ReflexAngle(angles[i])) return true;
    }
    return false;
}




// it will fail if there is not points
bool isPolygon(std::vector<Point>& points){
    if(points.size() < 1) return false;
    return true;
}

// it will fail if there is any sides are Parallel
bool isTriangle(std::vector<Point>& points){
    if(points.size() != 3) return false;
    else{
        Vector v1(points[0], points[1]);
        Vector v2(points[1], points[2]);
        Vector v3(points[0], points[2]);
        if(Parallel(v1, v2)||Parallel(v1, v3)||Parallel(v2, v3)){
            return false;
        }
    }
    return true;
}


// it will fail if no two sides are EqualSides
bool isIsoscelesTriangle(std::vector<Point>& points){
    if(!isTriangle(points))return false;
    else{
        double d1 = DistanceBetween(points[0], points[1]);
        double d2 = DistanceBetween(points[0], points[2]);
        double d3 = DistanceBetween(points[1], points[2]);
        if(EqualSides(d1,d2)||EqualSides(d1,d3)||EqualSides(d2, d3)){
            return true;
        }
        else return false;
    }
}

// it will fail if there is not RightAngle
bool isRightTriangle(std::vector<Point>& points){
    if(!isTriangle(points))return false;
    else{
        /*
        double a = Angle(points[0], points[1], points[2]);
        double b = Angle(points[0], points[2], points[1]);
        double c = Angle(points[1], points[0], points[2]);
        if(RightAngle(a)||RightAngle(b)||RightAngle(c)){
            return true;
        }
        else{
            return false;
        }
        */
        Polygon p("test", points);
        if(p.HasARightAngle()) return true;
        else return false;
    }
}

// it will fail if there is not ObtuseAngle
bool isObtuseTriangle(std::vector<Point>& points){
    if(!isTriangle(points)){
        return false;
    }
    else{
        Polygon p("test", points);
        if(p.HasAnObtuseAngle()) return true;
        else return false;
    }
}

// it will fail if it is not IsoscelesTriangle and ObtuseTriangle
bool isIsoscelesObtuseTriangle(std::vector<Point>& points){
    if(isIsoscelesTriangle(points) && isObtuseTriangle(points)) return true;
    else return false;
}

// it will fail if it is not IsoscelesTriangle and RightTriangle
bool isIsoscelesRightTriangle(std::vector<Point>& points){
    if(isIsoscelesTriangle(points) && isRightTriangle(points)) return true;
    else return false;
}

// it will fail if not all sides EqualSides
bool isEquilateralTriangle(std::vector<Point>& points){
    if(!isTriangle(points)){
        return false;
    }
    else{
        Polygon p("test", points);
        if(p.HasAllEqualSides()) return true;
        else return false;
    }
}

// it will success if there are 4 sides and not angles equal to 0 or 180
bool isQuadrilateral(std::vector<Point>& points){
    if(points.size() != 4) return false;
    else{
        std::vector<double> angles;
        getAngles(points, angles);
        for(int i = 0; i < angles.size(); ++ i){
            if(EqualAngles(angles[i], 0) || EqualAngles(angles[i], 180)) return false;
        }
        return true;
    }
}

// get all the sides of the shape
void getSides(std::vector<Point> points, std::vector<Vector> & v){
    for(int i = 0; i < points.size() - 1; ++ i){
        Vector vec(points[i], points[i + 1]);
        v.push_back(vec);
    }
    Vector vec(points[points.size() - 1], points[0]);
    v.push_back(vec);
}

// whether is Trapezoid or not
// it will success if any pair of sides are Parallel
bool isTrapezoid(std::vector<Point>& points){
    if(!isQuadrilateral(points)){
        return false;
    }
    else{
        std::vector<Vector> v;
        getSides(points, v);
        if(Parallel(v[0], v[2])||Parallel(v[1], v[3])){
            return true;
        }
        return false;
    }
}

// it will success if there are 2 near sides EqualSides
bool isKite(std::vector<Point>& points){
    if(!isQuadrilateral(points)){
        return false;
    }
    else{
        std::vector<Vector> v;
        getSides(points, v);
        if(EqualSides(v[0].Length(), v[1].Length())){
            if(EqualSides(v[2].Length(), v[3].Length())) return true;
            else return false;
        }
        else if(EqualSides(v[0].Length(), v[3].Length())){
            if(EqualSides(v[1].Length(), v[2].Length())) return true;
            else return false;
        }
        else return false;
        
    }
}

// it will success if there are 2 pair of sides Parallel
bool isParallelogram(std::vector<Point>& points){
    if(!isQuadrilateral(points)) return false;
    else{
        std::vector<Vector> v;
        getSides(points, v);
        if(Parallel(v[0], v[2]) && Parallel(v[1], v[3])) {
            return true;
        }
        else{
            return false;
        }
    }
}

// it will success if there it's concave
bool isArrow(std::vector<Point>& points){
    if(!isQuadrilateral(points)) return false;
    Polygon p("test", points);
    if(p.IsConcave()) return true;
    else return false;
}

// it will success if it's IsoscelesTrapezoid
bool isIsoscelesTrapezoid(std::vector<Point>& points){
    if(!isTrapezoid(points)) return false;
    else{
        std::vector<Vector> v;
        getSides(points, v);
        if(Parallel(v[0], v[2])){
            if(EqualSides(v[1].Length(), v[3].Length())){
                Polygon p("test", points);
                if(p.HasARightAngle()){
                    return true;
                }
                else{
                    if(!Parallel(v[1], v[3])) return true;
                    else return false;
                }
            }
            return false;
        }
        else if(Parallel(v[1], v[3])){
            if(EqualSides(v[0].Length(), v[2].Length())){
                Polygon p("test", points);
                if(p.HasARightAngle()){
                    return true;
                }
                else{
                    if(!Parallel(v[0], v[2])) return true;
                    else return false;
                }
            }
            return false;
        }
        return false;
    }
}

// it will success if it's Parallelogram and Kite
bool isRhombus(std::vector<Point>& points){
    if(isParallelogram(points) && isKite(points)){
        return true;
    }
    else return false;
}

// it will success if it's Parallelogram and IsoscelesTrapezoid
bool isRectangle(std::vector<Point>& points){
    /*
    if(isParallelogram(points) && isIsoscelesTrapezoid(points)) return true;
    else return false;
    */
    if(!isParallelogram(points)) return false;
    std::vector<double> angles;
    getAngles(points, angles);
    for(int i = 0; i < angles.size(); ++ i){
        if(!EqualAngles(angles[i], angles[0])) return false;
    }
    return true;
}

// it will success if it's Rhombus and Rectangle
bool isSquare(std::vector<Point>& points){
    if(isRhombus(points) && isRectangle(points)) return true;
    else return false;
}
