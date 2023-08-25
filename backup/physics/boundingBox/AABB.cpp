#include "../include/physics/boundingBox/AABB.h"

GameEgine::AABB::AABB()
    : min({0.0f, 0.0f, 0.0f}), max({0.0f, 0.0f, 0.0f})
{

}

GameEgine::AABB::AABB(const glm::vec3& _min, const glm::vec3& _max)
    : min(_min), max(_max)
{

}

GameEgine::AABB::~AABB()
{
    
}