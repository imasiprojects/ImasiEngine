#ifndef IMASIENGINE_RESOURCECONTAINER_HPP
#define IMASIENGINE_RESOURCECONTAINER_HPP

#include <map>

#include "../../ImasiEngine/Source/Graphics/Mesh.hpp"
#include "../../ImasiEngine/Source/Graphics/Material.hpp"
#include "../../ImasiEngine/Source/Graphics/Model.hpp"

namespace ImasiEngine
{
    template <typename KeyType = std::string>
    class ResourceContainer
    {
    private:

        static std::string getResourcePath(std::string& fileName)
        {
            return std::string("Resources/") + fileName;
        }

    protected:

        std::map<KeyType, Mesh*> _meshes;
        std::map<KeyType, ColorTexture2D*> _colorTextures;
        std::map<KeyType, Material*> _materials;
        std::map<KeyType, Model*> _models;

    public:

        /*ResourceContainer<KeyType>()
        {
        }*/

        ~ResourceContainer()
        {
            for (auto it : _meshes)
            {
                delete it.second;
            }

            for (auto it : _colorTextures)
            {
                delete it.second;
            }

            for (auto it : _materials)
            {
                delete it.second;
            }

            for (auto it : _models)
            {
                delete it.second;
            }
        }

        Mesh* getMesh(KeyType key)
        {
            auto it = _meshes.find(key);
            if (it != _meshes.end())
            {
                return it->second;
            }

            return nullptr;
        }

        ColorTexture2D* getColorTexture(KeyType key)
        {
            auto it = _colorTextures.find(key);
            if (it != _colorTextures.end())
            {
                return it->second;
            }

            return nullptr;
        }

        Material* getMaterial(KeyType key)
        {
            auto it = _materials.find(key);
            if (it != _materials.end())
            {
                return it->second;
            }

            return nullptr;
        }

        Material* getModel(KeyType key)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                return it->second;
            }

            return nullptr;
        }

        void set(KeyType key, Mesh&& value)
        {
            auto it = _meshes.find(key);
            if (it != _meshes.end())
            {
                delete it->second;
            }

            _meshes[key] = new Mesh(std::move(value));
        }

        void set(KeyType key, ColorTexture2D&& value)
        {
            auto it = _colorTextures.find(key);
            if (it != _colorTextures.end())
            {
                delete it->second;
            }

            _colorTextures[key] = new ColorTexture2D(std::move(value));
        }

        void set(KeyType key, Material&& value)
        {
            auto it = _materials.find(key);
            if (it != _materials.end())
            {
                delete it->second;
            }

            _materials[key] = new Material(std::move(value));
        }

        void set(KeyType key, Model&& value)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                delete it->second;
            }

            _models[key] = new Model(std::move(value));
        }
    };
}

#endif
