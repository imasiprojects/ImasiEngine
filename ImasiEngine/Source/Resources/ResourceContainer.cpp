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
        ColorTexture2D texture;

        if (!texture.loadFromFile(getResourcePath(fileName)))
        {
            Logger::out << "Error loading Texture (" << fileName << ")" << std::endl;
            return false;
        }

        add(key, std::move(texture));

        return true;
    }

    template <>
    void ResourceContainer::add(std::string key, Mesh&& value)
    {
        auto it = _meshes.find(key);
        if (it != _meshes.end())
        {
            delete it->second;
        }

        _meshes[key] = new Mesh(std::move(value));
    }

    template <>
    void ResourceContainer::add(std::string key, ColorTexture2D&& value)
    {
        auto it = _textures.find(key);
        if (it != _textures.end())
        {
            delete it->second;
        }

        _textures[key] = new ColorTexture2D(std::move(value));
    }

    template <>
    void ResourceContainer::add(std::string key, Material&& value)
    {
        auto it = _materials.find(key);
        if (it != _materials.end())
        {
            delete it->second;
        }

        _materials[key] = new Material(std::move(value));
    }

    template <>
    void ResourceContainer::add(std::string key, Model&& value)
    {
        auto it = _models.find(key);
        if (it != _models.end())
        {
            delete it->second;
        }

        _models[key] = new Model(std::move(value));
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
