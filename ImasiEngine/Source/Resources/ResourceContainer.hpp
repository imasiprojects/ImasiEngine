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

        std::map<KeyType, std::unique_ptr<Mesh>> _meshes;
        std::map<KeyType, std::unique_ptr<ColorTexture2D>> _colorTextures;
        std::map<KeyType, std::unique_ptr<Material>> _materials;
        std::map<KeyType, std::unique_ptr<Model>> _models;
        std::map<KeyType, std::unique_ptr<VertexShader>> _vertexShaders;
        std::map<KeyType, std::unique_ptr<FragmentShader>> _fragmentShaders;
        std::map<KeyType, std::unique_ptr<sf::Font>> _fonts;

    public:

        ResourceContainer() = default;

        Mesh* getMesh(KeyType key)
        {
            auto it = _meshes.find(key);
            if (it != _meshes.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        ColorTexture2D* getColorTexture(KeyType key)
        {
            auto it = _colorTextures.find(key);
            if (it != _colorTextures.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        Material* getMaterial(KeyType key)
        {
            auto it = _materials.find(key);
            if (it != _materials.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        Model* getModel(KeyType key)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        VertexShader* getVertexShader(KeyType key)
        {
            auto it = _vertexShaders.find(key);
            if (it != _vertexShaders.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        FragmentShader* getFragmentShader(KeyType key)
        {
            auto it = _fragmentShaders.find(key);
            if (it != _fragmentShaders.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        sf::Font* getFont(KeyType key)
        {
            auto it = _fonts.find(key);
            if (it != _fonts.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

        void set(KeyType key, Mesh&& value)
        {
            auto it = _meshes.find(key);
            if (it != _meshes.end())
            {
                it->second = std::make_unique<Mesh>(std::move(value));
            }
            else
            {
                _meshes[key] = std::make_unique<Mesh>(std::move(value));
            }
        }

        void set(KeyType key, ColorTexture2D&& value)
        {
            auto it = _colorTextures.find(key);
            if (it != _colorTextures.end())
            {
                it->second = std::make_unique<ColorTexture2D>(std::move(value));
            }
            else
            {
                _colorTextures[key] = std::make_unique<ColorTexture2D>(std::move(value));
            }
        }

        void set(KeyType key, Material&& value)
        {
            auto it = _materials.find(key);
            if (it != _materials.end())
            {
                it->second = std::make_unique<Material>(std::move(value));
            }
            else
            {
                _materials[key] = std::make_unique<Material>(std::move(value));
            }
        }

        void set(KeyType key, Model&& value)
        {
            auto it = _models.find(key);
            if (it != _models.end())
            {
                it->second = std::make_unique<Model>(std::move(value));
            }
            else
            {
                _models[key] = std::make_unique<Model>(std::move(value));
            }
        }

        void set(KeyType key, VertexShader&& value)
        {
            auto it = _vertexShaders.find(key);
            if (it != _vertexShaders.end())
            {
                it->second = std::make_unique<VertexShader>(std::move(value));
            }
            else
            {
                _vertexShaders[key] = std::make_unique<VertexShader>(std::move(value));
            }
        }

        void set(KeyType key, FragmentShader&& value)
        {
            auto it = _fragmentShaders.find(key);
            if (it != _fragmentShaders.end())
            {
                it->second = std::make_unique<FragmentShader>(std::move(value));
            }
            else
            {
                _fragmentShaders[key] = std::make_unique<FragmentShader>(std::move(value));
            }
        }

        void set(KeyType key, sf::Font&& value)
        {
            auto it = _fonts.find(key);
            if (it != _fonts.end())
            {
                it->second = std::make_unique<sf::Font>(std::move(value));
            }
            else
            {
                _fonts[key] = std::make_unique<sf::Font>(std::move(value));
            }
        }

        void removeMesh(KeyType key)
        {
            _meshes.erase(key);
        }

        void removeColorTexture(KeyType key)
        {
            _colorTextures.erase(key);
        }

        void removeMaterial(KeyType key)
        {
            _materials.erase(key);
        }

        void removeModel(KeyType key)
        {
            _models.erase(key);
        }

        void removeVertexShader(KeyType key)
        {
            _vertexShaders.erase(key);
        }

        void removeFragmentShader(KeyType key)
        {
            _fragmentShaders.erase(key);
        }

        void removeFont(KeyType key)
        {
            _fonts.erase(key);
        }
    };
}

#endif
