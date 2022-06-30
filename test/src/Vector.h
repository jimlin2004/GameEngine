#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    int x, y;
    Vector();
    Vector(int x, int y);
    void Set_x(int x);
    void Set_y(int y);
    void Set(int x, int y);
    Vector* GetUnitVector();
    static Vector* GetUnitVector(const Vector* vec);
    double GetLength();
    static double GetLength(const Vector* vec);
    Vector operator+(const Vector &vec);
    Vector operator-(const Vector &vec);
    bool operator==(const Vector &vec);
};

#endif