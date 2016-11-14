#include "ResourceContainer.hpp"
#include "../../ImasiEngine/Source/Utils/Logger.hpp"

ResourceContainer::ResourceContainer()
{
}

ResourceContainer::~ResourceContainer()
{
    for (auto it : _textures)
    {
        delete it.second;
    }
}

template <>
bool ResourceContainer::load<ImasiEngine::ColorTexture2D>(std::string key, std::string fileName)
{
    ImasiEngine::ColorTexture2D* texture = new ImasiEngine::ColorTexture2D();

    if (!texture->loadFromFile(getResourcePath(fileName)))
    {
        ImasiEngine::Logger::out << "Error loading Texture (" << fileName << ")" << std::endl;
        return false;
    }

    auto it = _textures.find(key);
    if (it != _textures.end())
    {
        delete it->second;
    }

    _textures[key] = texture;

    return true;
}

template <>
ImasiEngine::ColorTexture2D* ResourceContainer::get(std::string key)
{
    auto it = _textures.find(key);
    if (it != _textures.end())
    {
        return it->second;
    }

    return nullptr;
}
