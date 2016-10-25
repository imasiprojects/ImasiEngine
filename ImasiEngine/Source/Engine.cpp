#include "Engine.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Preprocessor.hpp"
#include "Utils/OpenglDebugger.hpp"
#include "Utils/SfmlOpengl.hpp"

namespace ImasiEngine
{
    Engine::Engine()
    {
        _window = nullptr;

        Logger::out << std::endl;
        Logger::out << " IscEngine" << std::endl;
        Logger::out << " -----------------------" << std::endl << std::endl;
    }

    Engine::~Engine()
    {
        safeDelete(_window);
    }

    Window* Engine::getWindow() const
    {
        return _window;
    }

    void Engine::create(const std::string& title, const unsigned int width, const unsigned int height, const unsigned int style)
    {
        Logger::out << " Creating context..." << std::endl << std::endl;

        sf::ContextSettings contextSettings;
        contextSettings.depthBits = 24;
        contextSettings.stencilBits = 8;
        contextSettings.antialiasingLevel = 0;
        contextSettings.majorVersion = 2;
        contextSettings.minorVersion = 1;

        _window = new Window(sf::VideoMode(width, height), title, style, contextSettings);
        _window->setVerticalSyncEnabled(false);
        _window->setFramerateLimit(160);

        contextSettings = _window->getSettings();
        Logger::out << "  >> " << glGetString(GL_VENDOR) << " | " << glGetString(GL_RENDERER) << std::endl;
        Logger::out << "  >> OpenGL " << contextSettings.majorVersion << "." << contextSettings.minorVersion << std::endl;
        Logger::out << "  >> Depth: " << contextSettings.depthBits << ", Stencil: " << contextSettings.stencilBits << ", Antialiasing: " << contextSettings.antialiasingLevel << std::endl;

        if (contextSettings.majorVersion < 3)
        {
            Logger::out << std::endl << "  ## No compatible graphics card found" << std::endl;
            return;
        }

        Logger::out << std::endl;

        setupGlew();
        setupOpenGL();
    }

    void Engine::setupGlew()
    {
        Logger::out << " Initializing GLEW..." << std::endl << std::endl;

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            Logger::out << "  >> Error initializing GLEW" << std::endl;
        }
        else
        {
            Logger::out << "  >> Using GLEW v" << glewGetString(GLEW_VERSION) << std::endl;
        }

        if (GLEW_ARB_vertex_array_object)
        {
            Logger::out << "  >> Using VAO" << std::endl;
        }
        else
        {
            Logger::out << "  >> Using VBO :'(" << std::endl;
        }

        Logger::out << std::endl;
    }

    void Engine::setupOpenGL()
    {
        // Clear color
        GL(glClearColor(1.0f, 0.7f, 0.1f, 1.0f));

        // Backface culling
        GL(glEnable(GL_CULL_FACE));
        GL(glCullFace(GL_BACK));
        GL(glFrontFace(GL_CCW));

        // Depth control
        GL(glEnable(GL_DEPTH_TEST));
        GL(glDepthFunc(GL_LEQUAL));

        // Transparency
        GL(glEnable(GL_BLEND));
        GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void Engine::processWindowEvents()
    {
        sf::Event windowEvent;
        while (_window->pollEvent(windowEvent))
        {
            processWindowEvent(windowEvent);
        }
    }

    float p = 0;

    void Engine::loop()
    {
        processWindowEvents();

        glViewport(0, 0, _window->getSize().x, _window->getSize().y);
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        SfmlOpengl::beginSfml(_window);

        sf::CircleShape a(p += 0.1f);
        a.setPosition(_window->getSize().x / 2.f + 50, 250);
        a.setFillColor(sf::Color::Green);
        _window->draw(a);

        SfmlOpengl::endSfml(_window);

        GL(glMatrixMode(GL_MODELVIEW));
        GL(glLoadIdentity());

        GL(glColor3ub(230, 57, 56));
        glBegin(GL_QUADS);
            glVertex3f(-p / 250, 0.3f, 0.0f);
            glVertex3f(-0.3f, -p / 250, 0.0f);
            glVertex3f(0.3f, -0.3f, 0.0f);
            glVertex3f(0.3f, 0.3f, 0.0f);
        GL(glEnd());

        SfmlOpengl::beginSfml(_window);

        sf::CircleShape b(p += 0.1f);
        b.setFillColor(sf::Color::Blue);
        _window->draw(b);

        SfmlOpengl::endSfml(_window);

        GL_CHECK();
        _window->display();
    }

    void Engine::processWindowEvent(const sf::Event event)
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                _window->close();
                break;
            }

            case sf::Event::Resized:
            {
                glViewport(0, 0, event.size.width, event.size.height);
                break;
            }

            case sf::Event::GainedFocus:
            {
                _window->setFocus(true);
                break;
            }

            case sf::Event::LostFocus:
            {
                _window->setFocus(false);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    void Engine::run()
    {
        while (_window->isOpen())
        {
            loop();
        }
    }
}