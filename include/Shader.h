#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "../third_party/glm/glm.hpp"
#include "GameEngineAPI/GameEngineAPI.h"

//將OpenGL的shader抽象成的class
//load、complie、create shader
//使用GEngine->ShaderManager
//是為了效能考量(stringsteam的初始化效率低)
namespace GameEngine
{
    class Shader
    {
    private:
        unsigned int id;
        unsigned int getUniformLocation(const std::string& name);
        std::unordered_map<std::string, int> uniformLoactionTable;
    public:
        Shader();
        ~Shader();
        void bind();
        void unbind();
        void generateShader(const char* const VSPath, const char* const FSPath);
        //Todo: set uniform 一般化(template)
        void setUniform1i(const std::string& name, int value);
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
    };
}


#endif