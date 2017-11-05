#include <render/imageatlas.hpp>
#include <cmath>

namespace MNPRender {

    ImageAtlas::ImageResource::ImageResource(const sf::Image &image) {
        resourceData = image;
        localRect = sf::IntRect(0,0,resourceData.getSize().x,resourceData.getSize().y);
        normalizedRect = sf::FloatRect();
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

    bool ImageAtlas::pushResource(const std::string &resourceKey, const sf::Image &image) {
        std::map<std::string,ImageResource*>::iterator it;
        it = m_resources.find(resourceKey);
        if (it != m_resources.end()) {
            return false;
        }
        m_needsPacking = true;
        m_resources[resourceKey] = new ImageResource(image);
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

        int dims = std::ceil(std::sqrt(area));
        // above gets us the power of two that would contain everything assuming area
        // was PERFECTLY tightly packed (ie: dissecting rects up allowed)

        int xMark = 0;
        int yMark = 0;
        int yTemp = 0;

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

        int resultW = dims;
        int resultH = yMark;

        // note that we have to populate image on a second iteration here
        // because the estimate isn't perfect and yMark
        // CAN overflow the originally intended dims
        m_img.create(resultW,resultH);

        for (it = resourceLst.begin(); it != resourceLst.end(); ++it) {
            m_img.copy((*it)->resourceData,(*it)->localRect.left,(*it)->localRect.top);
            (*it)->normalizedRect.left = ((float)(*it)->localRect.left)/resultW;
            (*it)->normalizedRect.top = ((float)(*it)->localRect.top)/resultH;
            (*it)->normalizedRect.width = ((float)(*it)->localRect.width)/resultW;
            (*it)->normalizedRect.height = ((float)(*it)->localRect.height)/resultH;
        }
        m_texture.loadFromImage(m_img);
        m_needsPacking = false;
        return true;
    }

    bool ImageAtlas::getResource(const std::string &resourceKey, sf::FloatRect &textureRect) {
        if (m_needsPacking) {
            return false;
        }
        std::map<std::string,ImageResource*>::iterator it;
        it = m_resources.find(resourceKey);
        if (it == m_resources.end()) {
            return false;
        }
        textureRect = it->second->normalizedRect;
        return true;
    }

    sf::Texture &ImageAtlas::getTexture() {
        return m_texture;
    }
}
