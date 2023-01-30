#include "Renderer.h"

struct QuadData
{
    GameEngine::VertexArray* quadVertexArray;
    GameEngine::Shader* shader;
};

static QuadData* quadData;

void GameEngine::Renderer::initQuad()
{
    quadData = new QuadData();
    quadData->quadVertexArray = new GameEngine::VertexArray();
    quadData->quadVertexArray->generate();

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f,//0
        1.0f, 0.0f, 1.0f, 0.0f,//1
        1.0f, 1.0f, 1.0f, 1.0f,//2
        0.0f, 1.0f, 0.0f, 1.0f //3
    };
    // float vertices[] = {
    //     0.0f, 0.0f,
    //     50.0f, 0.0f,
    //     50.0f, 50.0f,
    //     0.0f, 50.0f
    // };

    VertexBuffer quadVB;
    quadVB.generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 2);
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    quadData->quadVertexArray->addBuffer(quadVB, layout);
    GameEngine::IndexBuffer quadIB;
    quadIB.generate(indices, sizeof(indices) / sizeof(unsigned int));
    quadData->shader = new GameEngine::Shader();
    quadData->shader->generateShader("../asset/shader/rect/rect.vs", "../asset/shader/rect/rect.fs");
    
    quadData->quadVertexArray->unbind();
    quadData->shader->unbind();
    quadVB.unbind();
    quadIB.unbind();
}

void GameEngine::Renderer::init()
{
    GameEngine::Renderer::initQuad();
}

void GameEngine::Renderer::begin()
{
    quadData->shader->bind();
    quadData->shader->setUniformMat4f("u_MVP", GameEngine::_currentCamera->getProjectionMatrix());
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
    quadData->shader->bind();
    quadData->shader->setUniform4f("u_color", color.x, color.y, color.z, color.w);
    quadData->shader->setUniformMat4f("u_transform", glm::translate(glm::mat4(1.0f), position) * 
        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f})
    );
    quadData->quadVertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}