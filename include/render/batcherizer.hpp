#pragma once
#include <SFML/graphics.hpp>
#include <vector>
#include <list>

#include <core/math.hpp>

namespace MNPRender {
    class Batcherizer {
        struct BatchBundle {
            MNPCore::Quad _vertices;
            sf::FloatRect _textureRect;
            float _depth;
            unsigned int _layersInfrontOf;
            BatchBundle(const MNPCore::Quad &vertices, const sf::FloatRect &textureRect, float depth);
            static bool batchBundleDepthCmp(const BatchBundle *a, const BatchBundle *b);
        };

        std::list<BatchBundle*> m_batchBundles;
        std::vector<sf::VertexArray> m_batches;

    public:
        Batcherizer();
        ~Batcherizer();

        void push(const MNPCore::Quad &vertices, const sf::FloatRect &textureRect, float depth);

        /*
            Batcherizes and also flushes all pushed batch bundles.
            The resulting vertex arrays are stored in m_batches to be retrieved
        */
        void batcherize();

        /*
            Intended to be used as a read-only only. Gives a set of individual vertex array batches
            which, when drawn in separate draw calls, guarantees maximum batch efficiency without
            apprehending blending.
        */
        std::vector<sf::VertexArray> &getBatches();
    };
}
