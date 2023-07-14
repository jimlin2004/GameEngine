#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "GL/glew.h"
#include "Core/GameObject.h"
#include <string>
#include <fstream>
#include <sstream>

namespace GameEngine
{
    class ShaderManager: public GameObject
    {
    public:
        ShaderManager();
        ~ShaderManager();
        std::string loadShader(const char* const filePath);
        unsigned int compileShader(unsigned int type, std::string source);
        unsigned int createShader(std::string vertexShader, std::string fragmentShader);
    private:
        std::stringstream ssBuffer;
    };
}

#endif