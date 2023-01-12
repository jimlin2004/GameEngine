#include "ShaderManager.h"

GameEngine::ShaderManager::ShaderManager()
{

}

GameEngine::ShaderManager::~ShaderManager()
{

}

std::string GameEngine::ShaderManager::loadShader(const char* const filePath)
{
    //清空
    this->ssBuffer.clear();
    this->ssBuffer.str("");
    std::ifstream stream(filePath);
    std::string line;
    while (std::getline(stream, line))
    {
        this->ssBuffer << line << '\n';
    }
    return this->ssBuffer.str();
}

unsigned int GameEngine::ShaderManager::compileShader(unsigned int type, std::string source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //error handle
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        printf("Failed to compile %s shader\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        printf("%s", message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int GameEngine::ShaderManager::createShader(std::string vertexShader, std::string fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = this->compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}