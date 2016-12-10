#include "InstancedRenderer.hpp"

#include <mutex>

#include "../Programs/VertexShader.hpp"
#include "../Programs/FragmentShader.hpp"
#include "../Models/Model.hpp"

namespace ImasiEngine
{
    const char* InstancedRenderer::_vertexShader = R"SHADER_END(

        #version 330 core

        layout(location = 0) in vec3 vertexPosition_modelspace;
        layout(location = 1) in vec2 vertexUV;
        layout(location = 2) in mat4 MVP;

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

    void InstancedRenderer::optimizeEntities(const glm::mat4& VP, std::map<Model*, std::list<ArrayBuffer*> >& finalOptimization) const
    {
        std::mutex initialOptimizationMutex;
        std::map<Model*, std::vector<glm::mat4>> initialOptimization;

        //std::list<std::thread> threads;

        {
            sf::Clock clock;

            for (auto& entityGroup : _entities)
            {
                //threads.push_back(std::thread([&]()
                {
                    for (auto& entity : entityGroup)
                    {
                        glm::mat4 MVP = VP * entity->getModelMatrix();

                        if (isVisible(MVP))
                        {
                            initialOptimizationMutex.lock();
                            initialOptimization[entity->model].push_back(MVP);
                            initialOptimizationMutex.unlock();
                        }
                    }
                }//));
            }

            std::cout << "Optimize entities: " << clock.restart().asMilliseconds() << std::endl;
        }

        /*for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }*/

        {
            sf::Clock clock;

            // TODO: Split into multiple ArrayBuffers

            for (auto& modelAndMVPs : initialOptimization)
            {
                ArrayBuffer* mvpBuffer = new ArrayBuffer(modelAndMVPs.second.data(), (unsigned int)modelAndMVPs.second.size());
                finalOptimization[modelAndMVPs.first].push_back(mvpBuffer);
            }

            std::cout << "Create Buffer(s): " << clock.restart().asMilliseconds() << std::endl;
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

    void InstancedRenderer::add(Entity* entity)
    {
        if (_entities.size() == 0 || _entities.back().size() >= _entities.back().capacity())
        {
            _entities.push_back(std::vector<Entity*>());
            _entities.back().reserve(_maxVectorSize);
        }

        std::vector<Entity*>& v = _entities.back();

        v.resize(v.size() + 1);
        v[v.size() - 1] = entity;
    }

    void InstancedRenderer::clear()
    {
        sf::Clock clock;
        _entities.clear();
        _vertexArray->detachAllBuffers();
        std::cout << "Clear: " << clock.restart().asMilliseconds() << std::endl;
    }

    void InstancedRenderer::render(const glm::mat4& VP)
    {
        std::map<Model*, std::list<ArrayBuffer*>> finalOptimization;
        optimizeEntities(VP, finalOptimization);

        sf::Clock clock;

        if (finalOptimization.size() > 0)
        {
            BIND(Program, _program);
            {
                for (auto& optimizedEntity : finalOptimization)
                {
                    auto& model = optimizedEntity.first;

                    BIND(Texture, model->material->diffuseMap, 0);
                    {
                        for (auto& arrayBuffer : optimizedEntity.second)
                        {
                            _vertexArray->attachMesh(model->mesh);
                            _vertexArray->attachArrayBuffer(arrayBuffer, ModelMatrix, 1);
                            _vertexArray->render();
                        }
                    }
                    UNBIND(Texture, 0);
                }
            }
            UNBIND(Program);
        }

        std::cout << "Render: " << clock.restart().asMilliseconds() << std::endl;

        // Clean memory!
        for (auto& pair : finalOptimization)
        {
            for (auto& arrayBuffer : pair.second)
            {
                delete arrayBuffer;
            }
        }
    }

    void InstancedRenderer::render(Camera& camera)
    {
        render(camera.getViewProjectionMatrix());
    }

    bool InstancedRenderer::isVisible(const glm::mat4& MVP, const glm::vec3& position) const
    {
        glm::vec4 model_cameraspace = MVP * glm::vec4(position, 1);

        float x = model_cameraspace.x / model_cameraspace.w;
        float y = model_cameraspace.y / model_cameraspace.w;

        return model_cameraspace.z >= 0.f
            && x >= -1.f && x <= 1.f
            && y >= -1.f && y <= 1.f;
    }
}
