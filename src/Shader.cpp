#include "Shader.h"

GameEngine::Shader::Shader()
{
    this->id = 0;
}

GameEngine::Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void GameEngine::Shader::generateShader(const char* const VSPath, const char* const FSPath)
{
    std::string vertexShader = GameEngine::GEngine->shaderManager->loadShader(VSPath);
    std::string fragmentShader = GameEngine::GEngine->shaderManager->loadShader(FSPath);
    this->id = GameEngine::GEngine->shaderManager->createShader(vertexShader, fragmentShader);
}

void GameEngine::Shader::bind()
{
    glUseProgram(this->id);
}

void GameEngine::Shader::unbind()
{
    glUseProgram(0);
}

unsigned int GameEngine::Shader::getUniformLocation(const std::string& name)
{
    if (this->uniformLoactionTable.find(name) != this->uniformLoactionTable.end())
        return this->uniformLoactionTable[name];
    int location = glGetUniformLocation(this->id, name.c_str());
    if (location == -1)
        printf("[Waring] uniform %s doesn't exist.\n", name.c_str());
    this->uniformLoactionTable[name] = location;
    return location;
}

void GameEngine::Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(this->getUniformLocation(name), value);
}

void GameEngine::Shader::setUniform4f(const std::string& name, const glm::vec4& value)
{
    glUniform4f(this->getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void GameEngine::Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}