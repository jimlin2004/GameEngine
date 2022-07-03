#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Graphics.h"

bool CheckCollision(Circle* c1, Circle* c2);
bool CheckCollision(Rect* r1, Rect* r2);
bool CheckCollision(Circle* c1, Rect* r1);

#endif