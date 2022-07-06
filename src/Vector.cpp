#include "Vector.h"
#include <cmath>

Vector::Vector()
{
    this->x = 0;
    this->y = 0;
}

Vector::Vector(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Vector::set_x(int x)
{
    this->x = x;
    return;
}

void Vector::set_y(int y)
{
    this->y = y;
    return;
}

void Vector::set(int x, int y)
{
    this->x = x;
    this->y = y;
    return;
}

double Vector::getLength()
{
    return (double)sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vector::getLength(const Vector* vec)
{
    return (double)sqrt(pow(vec->x, 2) + pow(vec->y, 2));
}

Vector Vector::operator+(const Vector &vec)
{
    return Vector(this->x + vec.x, this->y + vec.y);
}

Vector Vector::operator-(const Vector &vec)
{
    return Vector(this->x - vec.x, this->y - vec.y);
}

bool Vector::operator==(const Vector &vec)
{
    return (this->x == vec.x && this->y == vec.y);
}