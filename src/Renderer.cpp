#include "Renderer.h"

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float textureIndex;
};

struct RendererData
{
    const unsigned int maxQuads = 10000;
    const unsigned int maxVertices = maxQuads * 4;
    const unsigned int maxIndeices = maxQuads * 6;
    static const unsigned int maxTextureSlots = 32;

    GameEngine::VertexArray* quadVertexArray;
    GameEngine::VertexBuffer* quadVertexBuffer;
    GameEngine::Shader* textureShader;
    GameEngine::Texture* whiteTexture; // 事實為避免僅用color時出錯

    unsigned int quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;

    std::array<GameEngine::Texture*, maxTextureSlots> textureSlots;
    unsigned int textureSlotIndex = 1; // 0 is white texture
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

    rendererData.whiteTexture = new Texture(1, 1);
    unsigned int whiteTextureData = 0xffffffff;
    rendererData.whiteTexture->setData(&whiteTextureData);

    int samplers[rendererData.maxTextureSlots];
    for (unsigned int i = 0; i < rendererData.maxTextureSlots; ++i)
        samplers[i] = i;

    rendererData.textureShader = new GameEngine::Shader();
    rendererData.textureShader->generateShader("../asset/shader/rect/rect_with_texture.vs", "../asset/shader/rect/rect_with_texture.fs");
    rendererData.textureShader->bind();
    rendererData.textureShader->setUniform1iv("u_textures", samplers, rendererData.maxTextureSlots);

    //set white texture
    rendererData.textureSlots[0] = rendererData.whiteTexture;

    rendererData.quadVertexArray->unbind();
    // rendererData.textureShader->unbind();
    // // // quadVB.unbind();
    // rendererData.quadVertexBuffer->unbind();
    // quadIB.unbind();
}

void GameEngine::Renderer::init()
{
    GameEngine::Renderer::initQuad();
}

void GameEngine::Renderer::begin()
{
    rendererData.textureShader->bind();
    rendererData.textureShader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
    rendererData.quadIndexCount = 0;
    rendererData.quadVertexBufferPtr = rendererData.quadVertexBufferBase;
    rendererData.textureSlotIndex = 1;
}

void GameEngine::Renderer::close()
{
    GameEngine::Renderer::drawFrame();
}

void GameEngine::Renderer::drawFrame()
{
    rendererData.quadVertexBuffer->setData(rendererData.quadVertexBufferBase, (unsigned int)((uint8_t*) rendererData.quadVertexBufferPtr - (uint8_t*) rendererData.quadVertexBufferBase));
    for (unsigned int i = 0; i < rendererData.textureSlotIndex; ++i)
    {
        rendererData.textureSlots[i]->bind(i);
    }
    rendererData.textureShader->bind();
    rendererData.quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, rendererData.quadIndexCount, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, color);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
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
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, texture, maskColor);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
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
}