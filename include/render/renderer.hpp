#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <render/scene.hpp>
//#include <render/compositing.hpp>

namespace MNPRender {
    class Renderer {
        sf::RenderWindow m_window;

        // compositing
        //std::map<std::string,CompositingTree*> m_compositingTrees;
        std::map<std::string,Scene*> m_scenes;

    public:
        Renderer();
        ~Renderer();

        bool addScene(const std::string &sceneName, Scene &scene);
        bool removeScene(const std::string &sceneName);
        Scene *getScene(const std::string &sceneName);

        /*bool addCompositingTree(const std::string &treeName, CompositingTree &tree);
        bool removeCompositingTrees(const std::string &treeName);
        CompositingTree *getCompositingTree(const std::string &treeName);*/

        void update(const float &deltaTime);
    };
}
