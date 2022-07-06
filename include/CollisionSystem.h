#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Graphics.h"

bool checkCollision(Circle* c1, Circle* c2);
bool checkCollision(Rect* r1, Rect* r2);
bool checkCollision(Circle* c1, Rect* r1);

#endif