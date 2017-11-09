#include <engine/render/image-atlas.hpp>
#include <cmath>

namespace MNPRender {

    ImageAtlas::ImageResource::ImageResource(const sf::Image &image, const sf::Vector2f &_offset) {
        resourceData = image;
        localRect = sf::FloatRect(0,0,(float)resourceData.getSize().x,(float)resourceData.getSize().y);
        normalizedRect = sf::FloatRect();
        offset = _offset;
    }

    bool ImageAtlas::ImageResource::cmp(const ImageResource *a, const ImageResource *b) {
        if (a->localRect.height > b->localRect.height) {
            return true;
        } else if (a->localRect.height < b->localRect.height) {
            return false;
        } else {
            if (a->localRect.width > b->localRect.width) {
                return true;
            } else if (a->localRect.width < b->localRect.width) {
                return false;
            }
            return false;
        }
    }

    ImageAtlas::ImageAtlas() {
        m_needsPacking = true;
    }

    ImageAtlas::~ImageAtlas() {
        std::map<std::string,ImageResource*>::iterator it;
        for (it = m_resources.begin(); it != m_resources.end(); ++it) {
            delete it->second;
        }
    }

    bool ImageAtlas::pushResource(const std::string &resourceKey, const sf::Image &image, const sf::Vector2f &offset) {
        std::map<std::string,ImageResource*>::iterator it;
        it = m_resources.find(resourceKey);
        if (it != m_resources.end()) {
            return false;
        }
        m_needsPacking = true;
        m_resources[resourceKey] = new ImageResource(image,offset);
        return true;
    }

    bool ImageAtlas::pullResource(const std::string &resourceKey) {
        std::map<std::string,ImageResource*>::iterator it;
        it = m_resources.find(resourceKey);
        if (it == m_resources.end()) {
            return false;
        }
        m_needsPacking = true;
        delete it->second;
        m_resources.erase(it);
        return true;
    }

    bool ImageAtlas::pack() {
        if (!m_needsPacking) {
            return false;
        }
        std::list<ImageResource*> resourceLst;
        std::map<std::string,ImageResource*>::iterator mapIt;
        for (mapIt = m_resources.begin(); mapIt != m_resources.end(); ++mapIt) {
            resourceLst.push_back(mapIt->second);
        }
        resourceLst.sort(ImageResource::cmp);

        float area;

        std::list<ImageResource*>::iterator it;
        for (it = resourceLst.begin(); it != resourceLst.end(); ++it) {
            area += (*it)->localRect.width * (*it)->localRect.height;
        }

        float dims = std::ceil(std::sqrt(area));
        // above gets us the dimension of square that would contain everything assuming area
        // was PERFECTLY tightly packed (ie: dissecting rects up allowed)

        float xMark = 0;
        float yMark = 0;
        float yTemp = 0;

        for (it = resourceLst.begin(); it != resourceLst.end(); ++it) {
            if (xMark + (*it)->localRect.width > dims) {
                xMark = 0;
                yMark += yTemp;
                yTemp = 0;
            }
            (*it)->localRect.left = xMark;
            (*it)->localRect.top = yMark;
            xMark += (*it)->localRect.width;
            yTemp = std::max(yTemp, (*it)->localRect.height);
        }
        yMark += yTemp;

        float resultW = dims;
        float resultH = yMark;

        // note that we have to populate image on a second iteration here
        // because the estimate isn't perfect and yMark
        // CAN overflow the originally intended dims
        m_img.create((int)resultW,(int)resultH);

        for (it = resourceLst.begin(); it != resourceLst.end(); ++it) {
            m_img.copy((*it)->resourceData,(*it)->localRect.left,(*it)->localRect.top);
            (*it)->normalizedRect.left = (*it)->localRect.left / resultW;
            (*it)->normalizedRect.top = (*it)->localRect.top / resultH;
            (*it)->normalizedRect.width = (*it)->localRect.width / resultW;
            (*it)->normalizedRect.height = (*it)->localRect.height / resultH;
        }
        m_texture.loadFromImage(m_img);
        m_needsPacking = false;
        return true;
    }

    bool ImageAtlas::getResource(const std::string &resourceKey, sf::FloatRect &textureRect, sf::Vector2f &offset, bool normalized) {
        if (m_needsPacking) {
            return false;
        }
        std::map<std::string,ImageResource*>::iterator it;
        it = m_resources.find(resourceKey);
        if (it == m_resources.end()) {
            return false;
        }
        if (normalized) {
            textureRect = it->second->normalizedRect;
        } else {
            textureRect = it->second->localRect;
        }
        offset = it->second->offset;
        return true;
    }

    sf::Texture &ImageAtlas::getTexture() {
        return m_texture;
    }
}
