#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    int x, y;
    Vector();
    Vector(int x, int y);
    void set_x(int x);
    void set_y(int y);
    void set(int x, int y);
    Vector* getUnitVector();
    static Vector* getUnitVector(const Vector* vec);
    double getLength();
    static double getLength(const Vector* vec);
    Vector operator+(const Vector &vec);
    Vector operator-(const Vector &vec);
    bool operator==(const Vector &vec);
};

#endif