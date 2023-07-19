#include "Opengl/TextureManager.h"

GameEngine::TextureManager::TextureManager()
{
}

std::string GameEngine::TextureManager::getTextureFileName(uint32_t id) const
{
    auto it = this->textureMap.find(id);
    return (it == this->textureMap.end()) ? "" : it->second;
}

void GameEngine::TextureManager::registerTexture(uint32_t id, const std::string &textureFileName)
{
    this->textureMap.insert({id, textureFileName});
    this->registerTable.insert({textureFileName, id});
}

uint32_t GameEngine::TextureManager::exists(const std::string &textureFileName) const
{
    auto it = this->registerTable.find(textureFileName);
    return (it == this->registerTable.end()) ? 0 : it->second;
}
