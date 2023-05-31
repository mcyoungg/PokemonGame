#ifndef VECTOR2D_H
#define VECTOR2D_H

/*
* This call is used to represent a vector in the real plane
* (a set of x and y displacements)
*/
#include <iostream>
//#include "Point2D.h"
using namespace std;

class Vector2D{

    public:

    double x;
    double y;

    Vector2D();
    Vector2D(double in_x, double in_y);

};

ostream& operator << (ostream &output, const Vector2D &v);

Vector2D operator* (const Vector2D &v, double d);

Vector2D operator/ (const Vector2D &v, double d);

#endif