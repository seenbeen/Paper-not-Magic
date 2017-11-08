#pragma once
#include <SFML/graphics.hpp>
#include <string>
#include <map>
#include <list>
#include <utility>

namespace MNPRender {
    class ImageAtlas {
        struct ImageResource {
            sf::FloatRect normalizedRect;
            sf::FloatRect localRect;
            sf::Vector2f offset;
            sf::Image resourceData;
            ImageResource(const sf::Image &image, const sf::Vector2f &offset);
            static bool cmp(const ImageResource *a, const ImageResource *b);
        };

        sf::Image m_img;
        sf::Texture m_texture;
        bool m_needsPacking;

        std::map<std::string,ImageResource*> m_resources;
    public:
        ImageAtlas();
        ~ImageAtlas();

        /*
            Push a resource from the atlas, effectively adding it to the texture
            on the next pack operation. Will invalidate the packed state.
            Returns false on:
            - The resource already exists
        */
        bool pushResource(const std::string &resourceKey, const sf::Image &image, const sf::Vector2f &offset);

        /*
            Pull a resource from the atlas, effectively removing it from the
            texture on the next pack operation. Will invalidate the packed state.
            Returns false on:
            - the resource doesn't exist
        */
        bool pullResource(const std::string &resourceKey);

        /*
            A pretty expensive operation which takes all currently pushed resources and
            packs them into an image. It then uploads the texture to the gpu.
            Returns false on:
            - the atlas has already been packed
        */
        bool pack();

        /*
            Fetches a resource from a packed imageAtlas and stores it in argument.
            Normalized determines whether the values should be divided by the texture dims
            to produce a value in the range [0,1]
            Returns false on:
            - atlas isn't packed
            - resource wasn't found
        */
        bool getResource(const std::string &resourceKey,  sf::FloatRect &textureRect, sf::Vector2f &offset, bool normalized = true);

        /*
            Do not modify the texture returned by this! It is meant to give a handle
            to the texture held by this atlas for read-only purposes. Will return the
            last valid, packed image texture. If no packing has happened yet, returns
            an invalid 0 by 0 texture.
        */
        sf::Texture &getTexture();
    };
}
