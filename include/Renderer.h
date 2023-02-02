#ifndef RENDERER_H
#define RENDERER_H

#include <array>
#include <GL/glew.h>
#include "../third_party/glm/glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "GameEngineAPI/GameEngineAPI.h"

namespace GameEngine
{
    /*
        author: JimLin
        作用: 渲染
        note: 純static，無記憶變數(變數以static記憶在外部)
    */
    class Renderer
    {
    public:
        //初始化Renderer，使用前須call 此 init()
        static void init();
        //執行渲染前需呼叫
        static void begin();
        //渲染的function呼叫完後需要調用此function
        static void close();
        //渲染四邊形(無z軸)，支援color
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        //渲染四邊形(含z軸)，支援color
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        //渲染四邊形(無z軸)，支援texture
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //渲染四邊形(含z軸)，支援texture
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //
        static void drawFrame();
    private:
        //初始化渲染四邊形需要的事物
        static void initQuad();
    };
}


#endif