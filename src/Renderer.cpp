#include "Renderer.h"

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
};

struct QuadData
{
    const unsigned int maxQuads = 10000;
    const unsigned int maxVertices = maxQuads * 4;
    const unsigned int maxIndeices = maxQuads * 6;

    GameEngine::VertexArray* quadVertexArray;
    GameEngine::VertexBuffer* quadVertexBuffer;
    GameEngine::Shader* textureShader;
    GameEngine::Texture* whiteTexture; // 事實為避免僅用color時出錯

    unsigned int quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;
};

static QuadData quadData;

void GameEngine::Renderer::initQuad()
{
    quadData.quadVertexArray = new GameEngine::VertexArray();
    quadData.quadVertexArray->generate();

    quadData.quadVertexBuffer = new GameEngine::VertexBuffer();
    quadData.quadVertexBuffer->generate(quadData.maxVertices * sizeof(QuadVertex));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); //position
    layout.push(GL_FLOAT, 4); //color
    layout.push(GL_FLOAT, 2); //texCrood
    quadData.quadVertexArray->addBuffer(*(quadData.quadVertexBuffer), layout);

    quadData.quadVertexBufferBase = new QuadVertex[quadData.maxVertices];
    unsigned int* quadIndeics = new unsigned int[quadData.maxIndeices];
    unsigned int offset = 0;
    for (unsigned int i = 0; i < quadData.maxIndeices; i += 6)
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
    // quadIB.generate(indices, sizeof(indices) / sizeof(unsigned int));
    quadIB.generate(quadIndeics, quadData.maxIndeices);
    quadIB.bind();
    delete[] quadIndeics;
    
    quadData.textureShader = new GameEngine::Shader();
    quadData.textureShader->generateShader("../asset/shader/rect/rect_with_texture.vs", "../asset/shader/rect/rect_with_texture.fs");
    quadData.textureShader->setUniform1i("u_texture", 0);

    quadData.whiteTexture = new Texture(1, 1);
    unsigned int whiteTextureData = 0xffffffff;
    quadData.whiteTexture->setData(&whiteTextureData);

    quadData.quadVertexArray->unbind();
    quadData.textureShader->unbind();
    // quadVB.unbind();
    quadData.quadVertexBuffer->unbind();
    quadIB.unbind();
}

void GameEngine::Renderer::init()
{
    GameEngine::Renderer::initQuad();
}

void GameEngine::Renderer::begin()
{
    quadData.textureShader->bind();
    quadData.textureShader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
    quadData.quadIndexCount = 0;
    quadData.quadVertexBufferPtr = quadData.quadVertexBufferBase;
}

void GameEngine::Renderer::close()
{
    quadData.quadVertexBuffer->setData(quadData.quadVertexBufferBase, (unsigned int)((uint8_t*) quadData.quadVertexBufferPtr - (uint8_t*) quadData.quadVertexBufferBase));

    GameEngine::Renderer::drawFrame();
}

void GameEngine::Renderer::drawFrame()
{
    quadData.quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, quadData.quadIndexCount, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, color);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    quadData.quadVertexBufferPtr->position = position;
    quadData.quadVertexBufferPtr->color = color;
    quadData.quadVertexBufferPtr->texCoord = {0.0f, 0.0f};
    quadData.quadVertexBufferPtr++;
    
    quadData.quadVertexBufferPtr->position = {position.x + size.x, position.y, position.z};
    quadData.quadVertexBufferPtr->color = color;
    quadData.quadVertexBufferPtr->texCoord = {1.0f, 0.0f};
    quadData.quadVertexBufferPtr++;

    quadData.quadVertexBufferPtr->position = {position.x + size.x, position.y + size.y, position.z};
    quadData.quadVertexBufferPtr->color = color;
    quadData.quadVertexBufferPtr->texCoord = {1.0f, 1.0f};
    quadData.quadVertexBufferPtr++;
    
    quadData.quadVertexBufferPtr->position = {position.x, position.y + size.y, position.z};
    quadData.quadVertexBufferPtr->color = color;
    quadData.quadVertexBufferPtr->texCoord = {0.0f, 1.0f};
    quadData.quadVertexBufferPtr++;
    
    quadData.quadIndexCount += 6;
    // quadData.textureShader->bind();
    // quadData.textureShader->setUniform4f("u_color", color);
    // quadData.whiteTexture->bind();
    // quadData.textureShader->setUniformMat4f("u_transform", glm::translate(glm::mat4(1.0f), position) * 
    //     glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f})
    // );
    // quadData.quadVertexArray->bind();
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, texture, maskColor);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    texture->bind();
    quadData.textureShader->bind();
    // quadData.textureShader->setUniform4f("u_color", maskColor);
    // quadData.textureShader->setUniformMat4f("u_transform", glm::translate(glm::mat4(1.0f), position) * 
    //     glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f})
    // );
    quadData.quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    texture->unbind();
}