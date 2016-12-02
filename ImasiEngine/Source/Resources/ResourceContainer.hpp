#ifndef IMASIENGINE_RESOURCECONTAINER_HPP
#define IMASIENGINE_RESOURCECONTAINER_HPP

#include <map>
#include <SFML/Graphics/Font.hpp>

#include "../../ImasiEngine/Source/Graphics/Meshes/Mesh.hpp"
#include "../../ImasiEngine/Source/Graphics/Materials/Material.hpp"
#include "../../ImasiEngine/Source/Graphics/Models/Model.hpp"
#include "../Graphics/Programs/VertexShader.hpp"
#include "../Graphics/Programs/FragmentShader.hpp"

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
        std::map<KeyType, VertexShader*> _vertexShaders;
        std::map<KeyType, FragmentShader*> _fragmentShaders;
        std::map<KeyType, sf::Font*> _fonts;

    public:

        ResourceContainer()
        {
        }

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

        Model* getModel(KeyType key)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                return it->second;
            }

            return nullptr;
        }

        VertexShader* getVertexShader(KeyType key)
        {
            auto it = _vertexShaders.find(key);
            if (it != _vertexShaders.end())
            {
                return it->second;
            }

            return nullptr;
        }

        FragmentShader* getFragmentShader(KeyType key)
        {
            auto it = _fragmentShaders.find(key);
            if (it != _fragmentShaders.end())
            {
                return it->second;
            }

            return nullptr;
        }

        sf::Font* getFont(KeyType key)
        {
            auto it = _fonts.find(key);
            if (it != _fonts.end())
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
                it->second = new Mesh(std::move(value));
            }
            else
            {
                _meshes[key] = new Mesh(std::move(value));
            }
        }

        void set(KeyType key, ColorTexture2D&& value)
        {
            auto it = _colorTextures.find(key);
            if (it != _colorTextures.end())
            {
                delete it->second;
                it->second = new ColorTexture2D(std::move(value));
            }
            else
            {
                _colorTextures[key] = new ColorTexture2D(std::move(value));
            }
        }

        void set(KeyType key, Material&& value)
        {
            auto it = _materials.find(key);
            if (it != _materials.end())
            {
                delete it->second;
                it->second = new Material(std::move(value));
            }
            else
            {
                _materials[key] = new Material(std::move(value));
            }
        }

        void set(KeyType key, Model&& value)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                delete it->second;
                it->second = new Model(std::move(value));
            }
            else
            {
                _models[key] = new Model(std::move(value));
            }
        }

        void set(KeyType key, VertexShader&& value)
        {
            auto it = _vertexShaders.find(key);
            if (it != _vertexShaders.end())
            {
                delete it->second;
                it->second = new VertexShader(std::move(value));
            }
            else
            {
                _vertexShaders[key] = new VertexShader(std::move(value));
            }
        }

        void set(KeyType key, FragmentShader&& value)
        {
            auto it = _fragmentShaders.find(key);
            if (it != _fragmentShaders.end())
            {
                delete it->second;
                it->second = new FragmentShader(std::move(value));
            }
            else
            {
                _fragmentShaders[key] = new FragmentShader(std::move(value));
            }
        }

        void set(KeyType key, sf::Font&& value)
        {
            auto it = _fonts.find(key);
            if (it != _fonts.end())
            {
                delete it->second;
                it->second = new sf::Font(std::move(value));
            }
            else
            {
                _fonts[key] = new sf::Font(std::move(value));
            }
        }
    };
}

#endif
