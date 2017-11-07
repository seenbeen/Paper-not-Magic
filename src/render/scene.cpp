#include <render/scene.hpp>

namespace MNPRender {
    Scene::Scene(ImageAtlas &imageAtlas) : m_imageAtlas(imageAtlas) {}

    Scene::~Scene() {
        std::set<SceneObject*>::iterator it;
        for (it = m_objects.begin(); it != m_objects.end(); ++it) {
            delete *it;
        }
    }

    bool Scene::addObject(SceneObject *object) {
        std::set<SceneObject*>::iterator it;
        it = m_objects.find(object);
        if (it != m_objects.end()) {
            return false;
        }
        m_objects.insert(object);
        return true;
    }

    bool Scene::removeObject(SceneObject *object) {
        std::set<SceneObject*>::iterator it;
        it = m_objects.find(object);
        if (it == m_objects.end()) {
            return false;
        }
        m_objects.erase(it);
        return true;
    }

    void Scene::update(const sf::Time &deltaTime) {
        std::set<SceneObject*>::iterator it;
        for (it = m_objects.begin(); it != m_objects.end(); ++it) {
            (*it)->update(deltaTime);
        }
    }

    void Scene::render(sf::RenderTarget &renderTarget) {
        std::set<SceneObject*>::iterator it;
        SceneObject *obj = NULL;
        for (it = m_objects.begin(); it != m_objects.end(); ++it) {
            obj = *it;
            sf::FloatRect textureRect;
            m_imageAtlas.getResource(obj->resource,textureRect,false);
            // will actually break on rotations right now!
            sf::Vector2f offset = obj->getResourceOffset();
            sf::FloatRect originalImageRect = sf::FloatRect(offset.x,offset.y,textureRect.width,textureRect.height);
            sf::FloatRect imageRect = obj->transform.transformRect(originalImageRect);

            m_batcherizer.push(imageRect,textureRect,obj->transform.depth());
        }
        m_batcherizer.batcherize();
        std::vector<sf::VertexArray> batches = m_batcherizer.getBatches();
        for (unsigned int i = 0; i < batches.size(); ++i) {
            renderTarget.draw(batches[i],&m_imageAtlas.getTexture());
        }
    }

    SceneObject::SceneObject(const std::string &resource) : resource(resource) {}
    SceneObject::~SceneObject() {}

    sf::Vector2f SceneObject::getResourceOffset() {
        return sf::Vector2f();
    }

    void SceneObject::update(const sf::Time &deltaTime) {}
}
