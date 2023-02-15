#include "Renderer.h"

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float textureIndex;
};

struct LineVertex
{
    glm::vec3 position;
    glm::vec4 color;
};

struct RendererData
{
    const unsigned int maxQuads = 10000;
    const unsigned int maxVertices = maxQuads * 4;
    const unsigned int maxIndeices = maxQuads * 6;
    static const unsigned int maxTextureSlots = 32;

    //Quad
    GameEngine::VertexArray* quadVertexArray;
    GameEngine::VertexBuffer* quadVertexBuffer;
    GameEngine::Shader* quadShader;

    unsigned int quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;

    //Line
    GameEngine::VertexArray* lineVertexArray;
    GameEngine::VertexBuffer* lineVertexBuffer;
    GameEngine::Shader* lineShader;
    float lineWidth = 1.0f;

    unsigned int lineVertexCount = 0;
    LineVertex* lineVertexBufferBase = nullptr;
    LineVertex* lineVertexBufferPtr = nullptr;

    GameEngine::Texture* whiteTexture; // 事實為避免僅用color時出錯
    std::array<GameEngine::Texture*, maxTextureSlots> textureSlots;
    unsigned int textureSlotIndex = 1; // 0 is white texture

    glm::vec4 quadVertexUnitPoint[4];
    GameEngine::RendererInfomation rendererInfomation;
};

static RendererData rendererData;

void GameEngine::Renderer::initQuad()
{
    rendererData.quadVertexArray = new GameEngine::VertexArray();
    rendererData.quadVertexArray->generate();
    rendererData.quadVertexArray->bind();
    
    rendererData.quadVertexBuffer = new GameEngine::VertexBuffer();
    rendererData.quadVertexBuffer->generate(rendererData.maxVertices * sizeof(QuadVertex));
    
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); //position
    layout.push(GL_FLOAT, 4); //color
    layout.push(GL_FLOAT, 2); //texCrood
    layout.push(GL_FLOAT, 1); //textureIndex
    rendererData.quadVertexArray->addBuffer(*(rendererData.quadVertexBuffer), layout);

    rendererData.quadVertexBufferBase = new QuadVertex[rendererData.maxVertices];
    unsigned int quadIndeics[rendererData.maxIndeices];
    unsigned int offset = 0;
    for (unsigned int i = 0; i < rendererData.maxIndeices; i += 6)
    {
        quadIndeics[i] = offset;
        quadIndeics[i + 1] = offset + 1;
        quadIndeics[i + 2] = offset + 2;
        quadIndeics[i + 3] = offset + 2;
        quadIndeics[i + 4] = offset + 3;
        quadIndeics[i + 5] = offset;

        offset += 4;
    }
    GameEngine::IndexBuffer quadIB;
    quadIB.generate(quadIndeics, rendererData.maxIndeices);
    rendererData.quadVertexArray->bind();
    quadIB.bind();
    // delete[] quadIndeics;

    int samplers[rendererData.maxTextureSlots];
    for (unsigned int i = 0; i < rendererData.maxTextureSlots; ++i)
        samplers[i] = i;

    rendererData.quadShader = new GameEngine::Shader();
    rendererData.quadShader->generateShader("../asset/shader/quad/quad.vs", "../asset/shader/quad/quad.fs");
    // rendererData.quadShader->generateShader("D:/code/cpp/gameGngine/asset/shader/quad/quad.vs", "D:/code/cpp/gameGngine/asset/shader/quad/quad.fs");
    rendererData.quadShader->bind();
    rendererData.quadShader->setUniform1iv("u_textures", samplers, rendererData.maxTextureSlots);
    
    // 設定單位四邊形座標
    rendererData.quadVertexUnitPoint[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    rendererData.quadVertexUnitPoint[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    rendererData.quadVertexUnitPoint[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    rendererData.quadVertexUnitPoint[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

    rendererData.quadVertexArray->unbind();
    // rendererData.quadShader->unbind();
    // // // quadVB.unbind();
    // rendererData.quadVertexBuffer->unbind();
    // quadIB.unbind();
}

void GameEngine::Renderer::initLine()
{
    rendererData.lineVertexArray = new GameEngine::VertexArray();
    rendererData.lineVertexArray->generate();
    rendererData.lineVertexArray->bind();
    
    rendererData.lineVertexBuffer = new GameEngine::VertexBuffer();
    rendererData.lineVertexBuffer->generate(rendererData.maxVertices * sizeof(LineVertex));
    
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); //position
    layout.push(GL_FLOAT, 4); //color
    rendererData.lineVertexArray->addBuffer(*(rendererData.lineVertexBuffer), layout);

    rendererData.lineVertexBufferBase = new LineVertex[rendererData.maxVertices];

    // rendererData.lineVertexArray->bind();

    rendererData.lineShader = new GameEngine::Shader();
    rendererData.quadShader->generateShader("../asset/shader/line/line.vs", "../asset/shader/line/line.fs");
    // rendererData.lineShader->generateShader("D:/code/cpp/gameGngine/asset/shader/line/line.vs", "D:/code/cpp/gameGngine/asset/shader/line/line.fs");
    rendererData.lineShader->bind();

    rendererData.lineVertexArray->unbind();
}

void GameEngine::Renderer::init()
{
    rendererData.whiteTexture = new Texture(1, 1);
    unsigned int whiteTextureData = 0xffffffff;
    rendererData.whiteTexture->setData(&whiteTextureData);
    // set white texture
    rendererData.textureSlots[0] = rendererData.whiteTexture;
    GameEngine::Renderer::initQuad();
    GameEngine::Renderer::initLine();
}

void GameEngine::Renderer::begin()
{
    rendererData.quadShader->bind();
    rendererData.quadShader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
    rendererData.quadIndexCount = 0;
    rendererData.quadVertexBufferPtr = rendererData.quadVertexBufferBase;
    rendererData.textureSlotIndex = 1;

    rendererData.lineShader->bind();
    rendererData.lineShader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
    rendererData.lineVertexCount = 0;
    rendererData.lineVertexBufferPtr = rendererData.lineVertexBufferBase;
}

void GameEngine::Renderer::close()
{
    GameEngine::Renderer::drawFrame();
}

void GameEngine::Renderer::resetInfomation()
{
    rendererData.rendererInfomation.drawCalls = 0;
    rendererData.rendererInfomation.quadNums = 0;
    rendererData.rendererInfomation.lineNums = 0;
}

void GameEngine::Renderer::startNewBatch()
{
    GameEngine::Renderer::close();

    rendererData.quadIndexCount = 0;
    rendererData.quadVertexBufferPtr = rendererData.quadVertexBufferBase;
    rendererData.textureSlotIndex = 1;

    rendererData.lineVertexCount = 0;
    rendererData.lineVertexBufferPtr = rendererData.lineVertexBufferBase;
}

void GameEngine::Renderer::drawFrame()
{
    if (rendererData.quadIndexCount)
    {
        rendererData.quadVertexBuffer->setData(rendererData.quadVertexBufferBase, (unsigned int)((uint8_t*) rendererData.quadVertexBufferPtr - (uint8_t*) rendererData.quadVertexBufferBase));
        for (unsigned int i = 0; i < rendererData.textureSlotIndex; ++i)
        {
            rendererData.textureSlots[i]->bind(i);
        }
        rendererData.quadShader->bind();
        rendererData.quadVertexArray->bind();
        glDrawElements(GL_TRIANGLES, rendererData.quadIndexCount, GL_UNSIGNED_INT, nullptr);
        rendererData.rendererInfomation.drawCalls++;
    }
    if (rendererData.lineVertexCount)
    {
        rendererData.lineVertexBuffer->setData(rendererData.lineVertexBufferBase, (unsigned int)((uint8_t*) rendererData.lineVertexBufferPtr - (uint8_t*) rendererData.lineVertexBufferBase));
        rendererData.lineShader->bind();
        rendererData.lineVertexArray->bind();
        glLineWidth(rendererData.lineWidth);
        glDrawArrays(GL_LINES, 0, rendererData.lineVertexCount);
        rendererData.rendererInfomation.drawCalls++;
    }
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, color);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();

    rendererData.quadVertexBufferPtr->position = position;
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y, position.z};
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, texture, maskColor);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();

    float textureIndex = 0.0f;

    for (unsigned int i = 1; i < rendererData.textureSlotIndex; ++i)
    {
        if (*(rendererData.textureSlots[i]) == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        textureIndex = (float)rendererData.textureSlotIndex;
        rendererData.textureSlots[rendererData.textureSlotIndex] = texture;
        rendererData.textureSlotIndex++;
    }

    rendererData.quadVertexBufferPtr->position = position;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, SubTexture* subTexture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, subTexture, maskColor);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, SubTexture* subTexture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();

    const glm::vec2* textureCroods = subTexture->getTextureCrood();
    GameEngine::Texture* texture = subTexture->getTexture();

    float textureIndex = 0.0f;

    for (unsigned int i = 1; i < rendererData.textureSlotIndex; ++i)
    {
        if (*(rendererData.textureSlots[i]) == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        textureIndex = (float)rendererData.textureSlotIndex;
        rendererData.textureSlots[rendererData.textureSlotIndex] = texture;
        rendererData.textureSlotIndex++;
    }

    rendererData.quadVertexBufferPtr->position = position;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[0];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[1];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = {position.x + size.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[2];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = {position.x, position.y + size.y, position.z};
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[3];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
    GameEngine::Renderer::drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[0];
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[1];
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[2];
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[3];
    rendererData.quadVertexBufferPtr->color = color;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = 0;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    GameEngine::Renderer::drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, maskColor);
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();
    
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    float textureIndex = 0.0f;

    for (unsigned int i = 1; i < rendererData.textureSlotIndex; ++i)
    {
        if (*(rendererData.textureSlots[i]) == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        textureIndex = (float)rendererData.textureSlotIndex;
        rendererData.textureSlots[rendererData.textureSlotIndex] = texture;
        rendererData.textureSlotIndex++;
    }

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[0];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[1];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[2];
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[3];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, SubTexture* subTexture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    GameEngine::Renderer::drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, subTexture, maskColor);
}

void GameEngine::Renderer::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, SubTexture* subTexture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    if (rendererData.quadIndexCount >= rendererData.maxIndeices)
        GameEngine::Renderer::startNewBatch();
    
    const glm::vec2* textureCroods = subTexture->getTextureCrood();
    GameEngine::Texture* texture = subTexture->getTexture();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
        * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    float textureIndex = 0.0f;

    for (unsigned int i = 1; i < rendererData.textureSlotIndex; ++i)
    {
        if (*(rendererData.textureSlots[i]) == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        textureIndex = (float)rendererData.textureSlotIndex;
        rendererData.textureSlots[rendererData.textureSlotIndex] = texture;
        rendererData.textureSlotIndex++;
    }

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[0];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[0];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[1];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[1];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;

    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[2];
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[2];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexUnitPoint[3];;
    rendererData.quadVertexBufferPtr->color = maskColor;
    rendererData.quadVertexBufferPtr->texCoord = textureCroods[3];
    rendererData.quadVertexBufferPtr->textureIndex = textureIndex;
    rendererData.quadVertexBufferPtr++;
    
    rendererData.quadIndexCount += 6;

    rendererData.rendererInfomation.quadNums++;
}

void GameEngine::Renderer::drawLine(const glm::vec2& point1, const glm::vec2& point2, const glm::vec4& color)
{
    GameEngine::Renderer::drawLine({point1.x, point1.y, 0.0f}, {point2.x, point2.y, 0.0f}, color);
}

void GameEngine::Renderer::drawLine(const glm::vec3& point1, const glm::vec3& point2, const glm::vec4& color)
{
    rendererData.lineVertexBufferPtr->position = point1;
    rendererData.lineVertexBufferPtr->color = color;
    rendererData.lineVertexBufferPtr++;

    rendererData.lineVertexBufferPtr->position = point2;
    rendererData.lineVertexBufferPtr->color = color;
    rendererData.lineVertexBufferPtr++;

    rendererData.lineVertexCount += 2;
    rendererData.rendererInfomation.lineNums++;
}

void GameEngine::Renderer::setLineWidth(float width)
{
    rendererData.lineWidth = width;
}

unsigned int GameEngine::Renderer::getQuadNum()
{
    return rendererData.rendererInfomation.quadNums;
}

unsigned int GameEngine::Renderer::getLineNum()
{
    return rendererData.rendererInfomation.lineNums;
}

unsigned int GameEngine::Renderer::getDrawCalls()
{
    return rendererData.rendererInfomation.drawCalls;
}