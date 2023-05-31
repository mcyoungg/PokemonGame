#include "Vector2D.h"
using namespace std;

Vector2D::Vector2D(){
    x = 0.0; 
    y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}


ostream& operator<< (ostream &output, const Vector2D &v){
    output << "<" << v.x << "," << v.y << ">"; 
    return output;
}

Vector2D operator* (const Vector2D &v, double d){
    Vector2D product; 
    product.x = v.x * d;
    product.y = v.y * d;
    return product; 
}

Vector2D operator/ (const Vector2D &v, double d){
    Vector2D quotient; 
    quotient.x = v.x / d;
    quotient.y = v.y / d;
    return quotient; 
}

