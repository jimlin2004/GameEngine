#include "src/Vector.h"
#include <iostream>

int main()
{
    Vector vec1(3, 4), vec2(1, 0);
    std::cout << Vector::GetLength(&vec2) <<'\n';
    return 0;
}