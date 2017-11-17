#pragma once
#include <string>
#include <map>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <engine/render/scene.hpp>
//#include <render/compositing.hpp>

namespace MNPRender {
    class Renderer {
        struct DebugShape {
            sf::Shape *shape;
            int depth;
            float duration;

            DebugShape(sf::Shape *shape, const int &depth, const float &duration);
            ~DebugShape();
            static bool compareDebugShape(const DebugShape *A, const DebugShape *B);
        };

        sf::RenderWindow &m_window;

        // compositing
        // std::map<std::string,CompositingTree*> m_compositingTrees;
        std::map<std::string,Scene*> m_scenes;

        std::list<DebugShape*> m_debugShapes;

        void renderDebugShapes(const float &deltaTime);

    public:
        Renderer(sf::RenderWindow &window);
        ~Renderer();

        bool addScene(const std::string &sceneName, Scene &scene);
        bool removeScene(const std::string &sceneName);
        Scene *getScene(const std::string &sceneName);

        /*bool addCompositingTree(const std::string &treeName, CompositingTree &tree);
        bool removeCompositingTrees(const std::string &treeName);
        CompositingTree *getCompositingTree(const std::string &treeName);*/

        /*
            A hack for now until the compositing tree is in, at which point debug rendering
            should probably be moved into individual compositing trees, and rendering will
            be done using proper viewports.
        */
        void update(const float &deltaTime);

        // debug drawing functions
        void debugCircleShape(const sf::CircleShape &shape, const int &depth, const float &duration=0.0f);
        void debugRectangleShape(const sf::RectangleShape &shape, const int &depth, const float &duration=0.0f);
        void debugConvexShape(const sf::ConvexShape &shape, const int &depth, const float &duration=0.0f);
    };
}
