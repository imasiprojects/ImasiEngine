#ifndef IMASIENGINE_OBJLOADER_HPP
#define IMASIENGINE_OBJLOADER_HPP

#include <iostream>
#include <vector>
#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include "../Graphics/Meshes/Mesh.hpp"
#include "../Utils/Logger.hpp"

static ImasiEngine::Mesh* loadMesh(const std::string& path)
{
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices);
    if (!scene)
    {
        ImasiEngine::Logger::out << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    if (scene->HasMeshes())
    {
        const aiMesh* mesh = scene->mMeshes[0];

        //vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D pos = mesh->mVertices[i];
            vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
        }

        // Fill vertices texture coordinates
        //uvs.reserve(mesh->mNumVertices);
        if (mesh->HasTextureCoords(0))
        {
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
                uvs.push_back(glm::vec2(UVW.x, UVW.y));
            }
        }

        // Fill face indices
        //indices.reserve(3 * mesh->mNumFaces);
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // Assume the model has only triangles.
            indices.push_back(mesh->mFaces[i].mIndices[0]);
            indices.push_back(mesh->mFaces[i].mIndices[1]);
            indices.push_back(mesh->mFaces[i].mIndices[2]);
        }
    }

    ImasiEngine::Mesh* mesh = new ImasiEngine::Mesh();
    mesh->setIndexBuffer(ImasiEngine::IndexBuffer(indices.data(), (int)(indices.size() / 3), 3));
    mesh->setVertexBuffer(ImasiEngine::ArrayBuffer(vertices.data(), vertices.size()));
    mesh->setUVBuffer(ImasiEngine::ArrayBuffer(uvs.data(), uvs.size()));

    return mesh;
    // The "scene" pointer will be deleted automatically by "importer"
}

#endif
