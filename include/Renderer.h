#ifndef RENDERER_H
#define RENDERER_H

#include <array>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Opengl/VertexArray.h"
#include "Opengl/IndexBuffer.h"
#include "Opengl/Shader.h"
#include "Opengl/Texture.h"
#include "Opengl/SubTexture.h"
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
        //執行批量渲染前需呼叫
        static void begin();
        //批量渲染的function呼叫完後需要調用此function
        static void close();
        //開始一個新的batch rendering
        static void startNewBatch();
        //預約批量渲染四邊形(無z軸)，支援color
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        //預約批量渲染四邊形(含z軸)，支援color
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        //預約批量渲染四邊形(無z軸)，支援texture
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染四邊形(含z軸)，支援texture
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        
        static void drawQuad(const glm::mat4& transform, Texture* texture, const glm::vec4& maskColor);
        //預約批量渲染四邊形(無z軸)，支援Subtexture
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, SubTexture* subTexture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染四邊形(含z軸)，支援Subtexture
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, SubTexture* subTexture, const glm::vec4& maskColor = glm::vec4(1.0f));
        
        static void drawQuad(const glm::mat4& transform, SubTexture* subTexture, const glm::vec4& maskColor);
        //預約批量渲染可旋轉四邊形(無z軸)，支援color
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        //預約批量渲染可旋轉四邊形(含z軸)，支援color
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        //預約批量渲染可旋轉四邊形(無z軸)，支援texture
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染可旋轉四邊形(含z軸)，支援texture
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, SubTexture* subTexture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染可旋轉四邊形(無z軸)，支援subTexture
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, SubTexture* subTexture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染可旋轉四邊形(含z軸)，支援subTexture
        //注意座標原點在四邊形中心
        static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture* texture, const glm::vec4& maskColor = glm::vec4(1.0f));
        //預約批量渲染畫線(無z軸)(支援color)
        static void drawLine(const glm::vec2& point1, const glm::vec2& point2, const glm::vec4& color);
        //預約批量渲染畫線(含z軸)(支援color)
        static void drawLine(const glm::vec3& point1, const glm::vec3& point2, const glm::vec4& color);
        
        //執行批量渲染，由close() 調用
        static void drawFrame();

        static void setLineWidth(float width);

        static unsigned int getQuadNum();
        static unsigned int getDrawCalls();
        static unsigned int getLineNum();
    private:
        //初始化渲染四邊形需要的事物
        static void initQuad();
        //初始化渲染線需要的事物
        static void initLine();
        static void resetInfomation();
    };

    struct RendererInfomation
    {
        unsigned int drawCalls = 0;
        unsigned int quadNums = 0;
        unsigned int lineNums = 0;
    };
}


#endif