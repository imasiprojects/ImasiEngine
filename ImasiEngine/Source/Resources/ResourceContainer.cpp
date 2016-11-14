#include "ResourceContainer.hpp"
#include "../../ImasiEngine/Source/Utils/Logger.hpp"

namespace ImasiEngine
{
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
    bool ResourceContainer::load<ColorTexture2D>(std::string key, std::string fileName)
    {
        ColorTexture2D* texture = new ColorTexture2D();

        if (!texture->loadFromFile(getResourcePath(fileName)))
        {
            Logger::out << "Error loading Texture (" << fileName << ")" << std::endl;
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
    ColorTexture2D* ResourceContainer::get(std::string key)
    {
        auto it = _textures.find(key);
        if (it != _textures.end())
        {
            return it->second;
        }

        return nullptr;
    }

    std::string ResourceContainer::getResourcePath(std::string& fileName)
    {
        return std::string("Resources/") + fileName;
    }
}
