#include <cmath>
#include "Point2D.h"

Point2D::Point2D(){
    x = 0.0;
    y = 0.0;
}

Point2D::Point2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(const Point2D &p1, const Point2D &p2){
    double dist = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
    return dist;
}

ostream& operator << (ostream &output, const Point2D &p){
    output << "(" << p.x << "," << p.y << ")"; 
    return output;
}

Point2D operator+ (const Point2D &p1, const Vector2D &v1){
    Point2D sum; 
    sum.x = p1.x + v1.x;
    sum.y = p1.y + v1.y;
    return sum; 
}

Vector2D operator- (const Point2D &p1, const Point2D &p2){
    Vector2D sum; 
    sum.x = p1.x - p2.x;
    sum.y = p1.y - p2.y;
    return sum; 
}

bool operator== (const Point2D &p1, const Point2D &p2){
    if(p1.x == p2.x && p1.y == p2.y){
        return true;
    }
    return false;
}
