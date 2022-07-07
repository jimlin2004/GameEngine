#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Graphics.h"
#include "GameBase.h"
#include <list>

class QuadTree
{
public:
    QuadTree();
    QuadTree(Boundary* bound);
    void clear();
    void subdivision();
    void insert(Actor* actor);
private:
    int maxObject;
    Boundary* bound;
    QuadTree* nodes[4];
    std::list<Actor*> container;
    int getQuadrant(Actor* actor);
};

bool checkCollision(Circle* c1, Circle* c2);
bool checkCollision(Rect* r1, Rect* r2);
bool checkCollision(Circle* c1, Rect* r1);
int distanceSquared(int x1, int y1, int x2, int y2);

#endif