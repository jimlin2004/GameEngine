#include "CollisionSystem.h"

QuadTree::QuadTree()
{
    return;
}

QuadTree::QuadTree(Boundary* bound)
{
    this->maxObject = 10;
    this->bound = bound;
}

void QuadTree::clear()
{
    for (int i = 0; i < 4; i++)
    {
        if (this->nodes[i])
        {
            this->nodes[i]->clear();
            this->nodes[i] = nullptr;
        }
    }
    return;
}

void QuadTree::subdivision()
{
    int sub_w = this->bound->getWidth() / 2;
    int sub_h = this->bound->getHeight() / 2;
    int x = this->bound->LT->x;
    int y = this->bound->LT->y;
    this->nodes[0] = new QuadTree(new Boundary(x + sub_w, y, sub_w, sub_h));
    this->nodes[1] = new QuadTree(new Boundary(x, y, sub_w, sub_h));
    this->nodes[2] = new QuadTree(new Boundary(x, y + sub_h, sub_w, sub_h));
    this->nodes[3] = new QuadTree(new Boundary(x + sub_w, y + sub_h, sub_w, sub_h));
}

int QuadTree::getQuadrant(Actor* actor)
{
    //預設在父節點回傳-1
    double w_midpoint = this->bound->LT->x + (this->bound->getWidth() / 2);
    double h_midpoint = this->bound->LT->y + (this->bound->getHeight() / 2);
    //Actor in I or II
    bool topQuadrant = actor->y + actor->h < h_midpoint;
    //Actor in III or IV
    bool bottomQuadtant = actor->y > h_midpoint;
    if (actor->x + actor->w < w_midpoint)
    {
        if (topQuadrant)
            return 1; // II
        else if (bottomQuadtant)
            return 2; // III
    }
    else if (actor->x > w_midpoint)
    {
        if (topQuadrant)
            return 0; // I
        else if (bottomQuadtant)
            return 3; // IV
    }
    return -1;
}

void QuadTree::insert(Actor* actor)
{
    if (this->nodes[0])
    {
        int quadrant = this->getQuadrant(actor);
        if (quadrant != -1)
        {
            this->nodes[quadrant]->insert(actor);
            return;
        }
    }
    //Actor 給 父節點
    this->container.emplace_back(actor);
    //超過容量
    if (this->container.size() > this->maxObject)
    {
        if (!this->nodes[0])
            this->subdivision();
        for (std::list<Actor*>::iterator it = this->container.begin(); it != this->container.end(); it++)
        {
            int quadrant = this->getQuadrant(*it);
            if (quadrant != -1)
            {
                this->nodes[quadrant]->insert(*it);
                it = this->container.erase(it);
            }
        }
    }
}

int distanceSquared(int x1, int y1, int x2, int y2)
{
    int s_x = x1 - x2;
    int s_y = y1 - y2;
    return (s_x * s_x) + (s_y * s_y);
}

bool checkCollision(Circle* c1, Circle* c2)
{
    int t_r = c1->radius + c2->radius;
    t_r *= t_r;
    return (distanceSquared(c1->x, c1->y, c2->x, c2->y) < t_r);
}