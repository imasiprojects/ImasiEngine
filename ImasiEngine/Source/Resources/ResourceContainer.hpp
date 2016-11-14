#ifndef IMASIENGINE_RESOURCECONTAINER_HPP
#define IMASIENGINE_RESOURCECONTAINER_HPP

#include <map>

#include "../../ImasiEngine/Source/Graphics/Mesh.hpp"
#include "../../ImasiEngine/Source/Graphics/Material.hpp"
#include "../../ImasiEngine/Source/Graphics/Model.hpp"

namespace ImasiEngine
{
    class ResourceContainer
    {
    private:

        static std::string getResourcePath(std::string& fileName);

    protected:

        std::map<std::string, Mesh*> _meshes;
        std::map<std::string, ColorTexture2D*> _textures;
        std::map<std::string, Material*> _materials;
        std::map<std::string, Model*> _models;

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
}

#endif
