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

void GameEngine::Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(this->getUniformLocation(name), v0, v1, v2, v3);
}