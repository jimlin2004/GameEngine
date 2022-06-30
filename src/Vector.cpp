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

void Vector::Set_x(int x)
{
    this->x = x;
    return;
}

void Vector::Set_y(int y)
{
    this->y = y;
    return;
}

void Vector::Set(int x, int y)
{
    this->x = x;
    this->y = y;
    return;
}

double Vector::GetLength()
{
    return (double)sqrt(pow(this->x, 2) + pow(this->y, 2));
}

double Vector::GetLength(const Vector* vec)
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