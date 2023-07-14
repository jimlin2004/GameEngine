#ifndef GAMEENGINE_MATH_H
#define GAMEENGINE_MATH_H

#include "glm/glm.hpp"

namespace GameEngine::Math
{
    bool decomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
}

#endif