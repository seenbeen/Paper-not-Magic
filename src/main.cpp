#include <SFML/Graphics.hpp>
#include <mnp/tower.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    sf::Clock clock;
    float r = 200.0f;
    MyDude d(400.0f - r, 300.0f - r, r);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        window.clear();
        d.update(elapsed, window);
        d.draw(window);
        window.display();
    }

    return 0;
}
