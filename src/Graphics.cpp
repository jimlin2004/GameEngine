#include "Graphics.h"

unsigned int GameEngine::Graphics::compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    //error handle
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        printf("Failed to compile %s shader\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        printf("%s", message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int GameEngine::Graphics::createShader(const char* const vertexShader, const char* const fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = GameEngine::Graphics::compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = GameEngine::Graphics::compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

GameEngine::Graphics::Graphics::Graphics(float x, float y)
{
    this->x = x;
    this->y = y;
}

void GameEngine::Graphics::Graphics::render()
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y, float width, float height): Graphics(x, y)
{
    this->width = width;
    this->height = height;
    this->processVBO();
    return;
}

void GameEngine::Graphics::Rect::processVBO()
{
    float vertices[6] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };
    glGenBuffers(1, &(this->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //usage
    // STATIC	資料只被設定一次，但會被使用很多次
    // DYNAMIC	資料被改變很多次，也被使用很多次
    // STREAM	資料每次繪製都會改變
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const char* const vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 pos;"
    "void main()\n"
    "{\n"
    "   gl_Position = pos;\n"
    "}\n";
    const char* const fragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
    unsigned int shader = GameEngine::Graphics::createShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}

void GameEngine::Graphics::Rect::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);

}