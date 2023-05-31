/*
* This class is used to represent a set of (x,y) Catresian coordinates.
*/
#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include "Vector2D.h"
using namespace std;


class Point2D{
    public:

    double x;
    double y;

    Point2D();
    Point2D(double in_x, double in_y);
};


double GetDistanceBetween(const Point2D &p1, const Point2D &p2);

ostream& operator << (ostream &output, const Point2D &p);

Point2D operator+ (const Point2D &p1, const Vector2D &v1);

Vector2D operator- (const Point2D &p1, const Point2D &p2);

bool operator== (const Point2D &p1, const Point2D &p2);



#endif