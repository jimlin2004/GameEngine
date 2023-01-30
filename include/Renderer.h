#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "../third_party/glm/glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameEngineAPI/GameEngineAPI.h"

namespace GameEngine
{
    /*
        渲染的api
    */
    class Renderer
    {
    public:
        static void init();
        static void begin();
        static void close();
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    private:
        static void initQuad();
    };
}


#endif