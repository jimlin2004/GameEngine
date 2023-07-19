#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <stdint.h>
#include <string>

namespace GameEngine
{
    class TextureManager
    {
    public:
        TextureManager();
        std::string getTextureFileName(uint32_t id) const;
        void registerTexture(uint32_t id, const std::string& textureFileName);
        uint32_t exists(const std::string& textureFileName) const;
    private:
        std::unordered_map<uint32_t, std::string> textureMap;
        std::unordered_map<std::string, uint32_t> registerTable;
    };
}

#endif