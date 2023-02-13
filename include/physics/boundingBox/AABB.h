#ifndef AABB_H
#define AABB_H

#include "../../../third_party/glm/glm.hpp"

namespace GameEgine
{
    class AABB
    {
    private:
        glm::vec3 max;
        glm::vec3 min;
    public:
        AABB();
        AABB(const glm::vec3& _min, const glm::vec3& _max);
        ~AABB();
    };
}

#endif