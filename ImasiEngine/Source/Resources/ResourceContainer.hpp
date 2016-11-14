#pragma once

#include <map>

#include "../../ImasiEngine/Source/Graphics/Mesh.hpp"
#include "../../ImasiEngine/Source/Graphics/Material.hpp"
#include "../../ImasiEngine/Source/Graphics/Model.hpp"

class ResourceContainer
{
private:

    static std::string getResourcePath(std::string& fileName)
    {
        return std::string("Resources/") + fileName;
    }

protected:

    std::map<std::string, ImasiEngine::Mesh*> _meshes;
    std::map<std::string, ImasiEngine::ColorTexture2D*> _textures;
    std::map<std::string, ImasiEngine::Material*> _materials;
    std::map<std::string, ImasiEngine::Model*> _models;

public:

    ResourceContainer();
    ~ResourceContainer();

    // ReSharper disable once CppFunctionIsNotImplemented
    template<typename T>
    bool load(std::string key, std::string fileName);

    // ReSharper disable once CppFunctionIsNotImplemented
    template<typename T>
    T* get(std::string key);
};
