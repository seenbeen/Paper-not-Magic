#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <engine/core/engine-config.hpp>
#include <engine/core/engine.hpp>
#include <engine/core/stage.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>
#include <engine/render/image-atlas.hpp>
#include <engine/render/scene.hpp>

#include <mnp/framework/ui/ui-elements.hpp>

#include <experimental/engine-demo.hpp>

namespace Experimental { namespace EngineDemos {
    using namespace MNPCore;
    using namespace MNPRender;

    void ComponentA::onLoad(Engine &engineContext, GameObject &objContext) {
        std::cout << "ComponentA on Load" << std::endl;
        m_timeOfExistence = 0.0f;
    }

    void ComponentA::onEnter(Engine &engineContext, GameObject &objContext) {
        std::cout << "ComponentA on Enter" << std::endl;
    }

    void ComponentA::onUpdate(Engine &engineContext, GameObject &objContext, const float &deltaTime) {
        /*if (m_timeOfExistence >= 5.0f) {
            engineContext.stop();
        }*/
        m_timeOfExistence += deltaTime;
    }

    void ComponentA::onPostUpdate(Engine &engineContext, GameObject &objContext) {}

    void ComponentA::onExit(Engine &engineContext, GameObject &objContext) {
        std::cout << "ComponentA on Exit" << std::endl;
    }

    void ComponentA::onUnload(Engine &engineContext, GameObject &objContext) {
        std::cout << "ComponentA on Unload" << std::endl;
    }

    ObjectA::ObjectA() {
        addComponent<ComponentA>("ComponentA");
    }

    StageA::StageA() : Stage(GAME) {
        addObject<ObjectA>("ObjectA");
        addObject<MyUIObject>("UIObject");
    }

    void StageA::onEnter(Engine &engineContext) {
        std::cout << "StageA onEnter" << std::endl;
        sf::RectangleShape debugShape(sf::Vector2f(100,80));
        debugShape.setFillColor(sf::Color::Green);
        debugShape.setPosition(sf::Vector2f(400-50,300-40));
        engineContext.getRenderer().debugRectangleShape(debugShape,2.5f);
    }

    void StageA::onUpdate(Engine &engineContext, const float &deltaTime) {}

    void StageA::onPostUpdate(Engine &engineContext) {}

    void StageA::onExit(Engine &EngineContext) {
        std::cout << "StageA onExit" << std::endl;
    }

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

    int EngineDemoA::run() {
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
        Scene myScene(atlas);
        setupScene(myScene);
        engine.getRenderer().addScene("testScene",myScene);

        std::cout << "This window will automatically close in ~5 seconds. Please wait..." << std::endl << std::endl;

        engine.run();
        engine.shutdown();
        return 0;
    }
}}
