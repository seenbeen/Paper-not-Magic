#include <SFML/graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <core/engine-config.hpp>
#include <core/engine.hpp>
#include <core/stage.hpp>
#include <core/game-object.hpp>
#include <core/game-object-component.hpp>
#include <render/image-atlas.hpp>
#include <render/scene.hpp>

using namespace MNPCore;
using namespace MNPRender;

class ObjectA;
class ComponentA : public GameObjectComponent<ObjectA> {
public:
    void onLoad(Engine &engineContext, ObjectA &objContext);
    void onEnter(Engine &engineContext, ObjectA &objContext);
    void onUpdate(Engine &engineContext, ObjectA &objContext, const float &deltaTime);
    void onExit(Engine &engineContext, ObjectA &objContext);
    void onUnload(Engine &engineContext, ObjectA &objContext);
};

class ObjectA : public GameObject<ObjectA> {
public:
    float timeOfExistence;
    ObjectA() : GameObject(*this) {
        timeOfExistence = 0;
        addComponent(new ComponentA());
    }
};

void ComponentA::onLoad(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Load" << std::endl;
}
void ComponentA::onEnter(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Enter" << std::endl;
}
void ComponentA::onUpdate(Engine &engineContext, ObjectA &objContext, const float &deltaTime) {
    if (objContext.timeOfExistence >= 5.0f) {
        engineContext.stop();
    }
    objContext.timeOfExistence += deltaTime;
    //std::cout << "ComponentA on Update Frame: " << objContext.timeOfExistence << std::endl;
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
    void onUpdate(Engine &engineContext, const float &deltaTime) {
        // std::cout << "StageA onUpdate" << std::endl;
    };
    void onExit(Engine &EngineContext) {
        std::cout << "StageA onExit" << std::endl;
    };
};

static bool loadAtlas(ImageAtlas &atlas) {
    std::ifstream inFile;
    inFile.open("asset/data.xml");
    if (!inFile) {
        std::cout << "rip couldn't find data file" << std::endl;
        return false;
    }
    std::string k, resource;
    sf::Image img;
    int oX, oY;
    while (inFile >> k >> k) {
        resource = "asset/testSprites/"+k.substr(7,k.length()-7-1);
        img.loadFromFile(resource);
        inFile >> k >> k;
        std::istringstream offX(k.substr(3,k.length()-3-1));
        inFile >> k;
        std::istringstream offY(k.substr(3,k.length()-3-1));
        offX >> oX;
        offY >> oY;
        atlas.pushResource(resource,img, sf::Vector2f(oX,oY));
    }
    return true;
}

static void setupScene(Scene &myScene) {
    SceneObject *objectA = new SceneObject("asset/testSprites/swingOF_0.png");
    objectA->transform.depth() = 1.0f;
    objectA->transform.position() += sf::Vector2f(400.0f,150.0f);
    myScene.addObject(objectA);

    SceneObject *objectB = new SceneObject("asset/testSprites/swingOF_1.png");
    objectB->transform.depth() = 0.0f;
    objectB->transform.position() += sf::Vector2f(200.0f,150.0f);
    myScene.addObject(objectB);

    SceneObject *objectC = new SceneObject("asset/testSprites/swingOF_1.png");
    objectC->transform.depth() = 0.0f;
    objectC->transform.position() += sf::Vector2f(400.0f,300.0f);
    objectC->transform.scale() *= 2.5f;
    objectC->transform.rotation() = 45.5f;
    myScene.addObject(objectC);
}

int main() {
    Engine engine;

    std::vector<Stage<EngineStages>*> stages;
    stages.push_back(new StageA());

    EngineConfig<EngineStages> config(GAME, stages);
    engine.initialize(&config);

    ImageAtlas atlas;
    if (!loadAtlas(atlas)) {
        return -1;
    }
    atlas.pack();

    sf::Texture text = atlas.getTexture();
    int texWidth = text.getSize().x;
    int texHeight = text.getSize().y;
    std::cout << "Result Dims: " <<  texWidth << "x" << texHeight << std::endl;

    Scene myScene(atlas);
    setupScene(myScene);
    engine.getRenderer().addScene("testScene",myScene);
    /*while (window.isOpen())
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
    }*/

    engine.run();
    engine.shutdown();
    return 0;
}
