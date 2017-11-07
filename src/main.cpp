#include <SFML/graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <core/engine.hpp>
#include <core/stage.hpp>
#include <core/gameobject.hpp>
#include <core/gameobjectcomponent.hpp>
#include <render/imageatlas.hpp>
#include <render/scene.hpp>

using namespace MNPCore;
using namespace MNPRender;

class ObjectA;
class ComponentA : public GameObjectComponent<ObjectA> {
public:
    void onLoad(Engine &engineContext, ObjectA &objContext);
    void onEnter(Engine &engineContext, ObjectA &objContext);
    void onUpdate(Engine &engineContext, ObjectA &objContext);
    void onExit(Engine &engineContext, ObjectA &objContext);
    void onUnload(Engine &engineContext, ObjectA &objContext);
};

class ObjectA : public GameObject<ObjectA> {
public:
    int framesOfExistance;
    ObjectA() : GameObject(*this) {
        framesOfExistance = 0;
        addComponent(new ComponentA());
    }
};

void ComponentA::onLoad(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Load" << std::endl;
}
void ComponentA::onEnter(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Enter" << std::endl;
}
void ComponentA::onUpdate(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Update Frame: " << objContext.framesOfExistance++ << std::endl;
    if (objContext.framesOfExistance == 5) {
        engineContext.stop();
    }
}
void ComponentA::onExit(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Exit" << std::endl;
}
void ComponentA::onUnload(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Unload" << std::endl;
}

enum EngineStages { MENU, GAME };

class StageA : public Stage<EngineStages> {
public:
    StageA() : Stage(GAME) {
        addObject(new ObjectA());
    }
    void onEnter(Engine &engineContext) {
        std::cout << "StageA onEnter" << std::endl;
    };
    void onUpdate(Engine &engineContext) {
        std::cout << "StageA onUpdate" << std::endl;
    };
    void onExit(Engine &EngineContext) {
        std::cout << "StageA onExit" << std::endl;
    };
};

int main() {
    ImageAtlas atlas;
    std::ifstream inFile;
    inFile.open("asset/data.xml");
    if (!inFile) {
        std::cout << "rip couldn't find data file" << std::endl;
    }
    std::string k, resource;
    sf::Image img;
    while (inFile >> k >> k) {
        resource = "asset/testSprites/"+k.substr(7,k.length()-7-1);
        img.loadFromFile(resource);
        atlas.pushResource(resource,img);
        inFile >> k >> k >> k;
    }
    atlas.pack();
    sf::Texture text = atlas.getTexture();
    sf::Sprite sprite(text);
    int texWidth = text.getSize().x;
    int texHeight = text.getSize().y;
    std::cout << "Result Dims: " <<  texWidth << "x" << texHeight << std::endl;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Seenbeen is(n't) boosted!",
                            sf::Style::Titlebar | sf::Style::Close, settings);

    Scene myScene(atlas);
    SceneObject *objectA = new SceneObject("asset/testSprites/swingOF_0.png");
    objectA->transform.depth() = 0.0f;
    myScene.addObject(objectA);

    SceneObject *objectB = new SceneObject("asset/testSprites/swingOF_1.png");
    objectB->transform.depth() = 1.0f;
    myScene.addObject(objectB);

    SceneObject *objectC = new SceneObject("asset/testSprites/swingOF_1.png");
    objectC->transform.depth() = 0.0f;
    objectC->transform.position() += sf::Vector2f(400.0f,300.0f);
    objectC->transform.scale() *= 1.5f;
    myScene.addObject(objectC);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        myScene.render(window);
        window.display();
    }

    return 0;
}
