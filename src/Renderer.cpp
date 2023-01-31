#include "Renderer.h"

struct QuadData
{
    GameEngine::VertexArray* quadVertexArray;
    GameEngine::Shader* textureShader;
    GameEngine::Texture* whiteTexture; // 事實為避免僅用color時出錯
};

static QuadData* quadData;

void GameEngine::Renderer::initQuad()
{
    quadData = new QuadData();
    quadData->quadVertexArray = new GameEngine::VertexArray();
    quadData->quadVertexArray->generate();

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//0
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//1
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,//2
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f //3
    };

    VertexBuffer quadVB;
    quadVB.generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3);
    layout.push(GL_FLOAT, 2);
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    quadData->quadVertexArray->addBuffer(quadVB, layout);
    GameEngine::IndexBuffer quadIB;
    quadIB.generate(indices, sizeof(indices) / sizeof(unsigned int));
    quadData->textureShader = new GameEngine::Shader();
    quadData->textureShader->generateShader("../asset/shader/rect/rect_with_texture.vs", "../asset/shader/rect/rect_with_texture.fs");
    quadData->textureShader->setUniform1i("u_texture", 0);

    quadData->whiteTexture = new Texture(1, 1);
    unsigned int whiteTextureData = 0xffffffff;
    quadData->whiteTexture->setData(&whiteTextureData);

    quadData->quadVertexArray->unbind();
    quadData->textureShader->unbind();
    quadVB.unbind();
    quadIB.unbind();
}

void GameEngine::Renderer::init()
{
    GameEngine::Renderer::initQuad();
}

void GameEngine::Renderer::begin()
{
    quadData->textureShader->bind();
    quadData->textureShader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
}

void GameEngine::Renderer::close()
{

}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, color);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    quadData->textureShader->bind();
    quadData->textureShader->setUniform4f("u_color", color);
    quadData->whiteTexture->bind();
    quadData->textureShader->setUniformMat4f("u_transform", glm::translate(glm::mat4(1.0f), position) * 
        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f})
    );
    quadData->quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GameEngine::Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    
    GameEngine::Renderer::drawQuad({position.x, position.y, 0.0f}, size, texture, maskColor);
}

void GameEngine::Renderer::drawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture, const glm::vec4& maskColor/* = glm::vec4(1.0f)*/)
{
    texture->bind();
    quadData->textureShader->bind();
    quadData->textureShader->setUniform4f("u_color", maskColor);
    quadData->textureShader->setUniformMat4f("u_transform", glm::translate(glm::mat4(1.0f), position) * 
        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f})
    );
    quadData->quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    texture->unbind();
}