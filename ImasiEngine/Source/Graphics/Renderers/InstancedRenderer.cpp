#include "InstancedRenderer.hpp"

#include "../Shaders/VertexShader.hpp"
#include "../Shaders/FragmentShader.hpp"
#include "../Model.hpp"

namespace ImasiEngine
{
    const char* InstancedRenderer::_vertexShader = R"SHADER_END(

        #version 330 core

        layout(location = 0) in vec3 vertexPosition_modelspace;
        layout(location = 1) in vec2 vertexUV;

        uniform mat4 MVP;

        out vec2 UV;

        void main()
        {
            UV = vertexUV;
            gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
        }

    )SHADER_END";

    const char* InstancedRenderer::_fragmentShader = R"SHADER_END(

        #version 330 core

        in vec2 UV;
        out vec3 color;

        uniform sampler2D myTexture;

        void main()
        {
            color = texture(myTexture, UV).rgb;
        }

    )SHADER_END";

    void InstancedRenderer::prepareOptimizedEntities(glm::mat4& VP)
    {
        std::list<std::thread> threads;

        for (auto& entityGroup : _entities)
        {
            threads.push_back(std::thread([&]()
            {
                for (auto& entity : entityGroup)
                {
                    glm::mat4 MVP = VP * entity->getModelMatrix();

                    if (isVisible(MVP))
                    {
                        _optimizedEntitiesMutex.lock();
                        _optimizedEntities[entity->model].push_back(MVP);
                        _optimizedEntitiesMutex.unlock();
                    }
                }
            }));
        }

        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    InstancedRenderer::InstancedRenderer(unsigned int maxVectorSize)
        : Renderer()
        , _program(new Program())
        , _vertexArray(new VertexArray())
        , _maxVectorSize(maxVectorSize)
    {
        VertexShader vertexShader(_vertexShader);
        FragmentShader fragmentShader(_fragmentShader);

        _program->attach(vertexShader);
        _program->attach(fragmentShader);

        if (!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
        }
    }

    InstancedRenderer::~InstancedRenderer()
    {
        delete _program;
        delete _vertexArray;
    }

    void InstancedRenderer::add(const std::list<Entity*>& entities)
    {
        sf::Clock clock;

        unsigned int count = 0;
        auto it = entities.begin();

        while (count < entities.size())
        {
            if (_entities.size() == 0 || _entities.back().size() >= _entities.back().capacity())
            {
                _entities.push_back(std::vector<Entity*>());
                _entities.back().reserve(_maxVectorSize);
            }

            std::vector<Entity*>& v = _entities.back();
            unsigned int vectorSize = (unsigned int)v.size();

            if (entities.size() - count >= v.capacity() - vectorSize)
            {
                v.resize(v.capacity());
                for (unsigned int i = vectorSize; i < v.capacity(); i++)
                {
                    v[i] = *it++;
                }
                count += v.capacity() - vectorSize;
            }
            else
            {
                v.resize(vectorSize + entities.size() - count);
                for (int i = vectorSize; i < entities.size() - count; i++)
                {
                    v[i] = *it++;
                }
                count = entities.size();
            }
        }

        std::cout << "Add entities: " << clock.restart().asMilliseconds() << std::endl;
    }

    void InstancedRenderer::clear()
    {
        sf::Clock clock;
        _entities.clear();
        _optimizedEntities.clear();
        std::cout << "Clear: " << clock.restart().asMilliseconds() << std::endl;

    }

    void InstancedRenderer::render(glm::mat4& VP)
    {
        sf::Clock clock;
        prepareOptimizedEntities(VP);
        std::cout << "Process entities: " << clock.restart().asMilliseconds() << std::endl;

        BIND(Program, _program);
        {
            for (auto& optimizedEntity : _optimizedEntities)
            {
                auto& model = optimizedEntity.first;

                BIND(Texture, model->material->diffuseMap, 0);
                {
                    for (glm::mat4& modelMatrix : optimizedEntity.second)
                    {
                        _program->setUniform("MVP", modelMatrix);
                        _vertexArray->attachMesh(model->mesh);
                        _vertexArray->render();
                    }
                }
                UNBIND(Texture, 0);
            }
        }
        UNBIND(Program);

        std::cout << "Render: " << clock.restart().asMilliseconds() << std::endl;
    }

    void InstancedRenderer::render(Camera& camera)
    {
        render(camera.getViewProjectionMatrix());
    }

    bool InstancedRenderer::isVisible(glm::mat4& MVP, glm::vec3& position) const
    {
        glm::vec4 model_cameraspace = MVP * glm::vec4(position, 1);

        float x = model_cameraspace.x / model_cameraspace.w;
        float y = model_cameraspace.y / model_cameraspace.w;

        return model_cameraspace.z >= 0.f
            && x >= -1.f && x <= 1.f
            && y >= -1.f && y <= 1.f;
    }
}
