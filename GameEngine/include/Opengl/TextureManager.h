#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <queue>
#include <stdint.h>
#include <string>

namespace GameEngine
{
    class Texture;

    struct CreateTextureTask
    {
        std::string textureFilePath;
        GameEngine::Texture* texture;
        int filter;
    };

    class TextureManager
    {
    public:
        TextureManager();
        std::string getTextureFileName(uint32_t id) const;
        void registerTexture(uint32_t id, const std::string& textureFileName);
        uint32_t exists(const std::string& textureFileName) const;
        //Opengl genTexture需要在glThread中，所以其他Thread的需要用此method
        void createTexture(const std::string& textureFilePath, GameEngine::Texture* texture, int filter);
        void processCreateTextureTasks();
    private:
        std::unordered_map<uint32_t, std::string> textureMap;
        std::unordered_map<std::string, uint32_t> registerTable;
        std::queue<CreateTextureTask> tasksQueue;
    };
}

#endif