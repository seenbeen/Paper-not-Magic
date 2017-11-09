#include <SFML/Graphics.hpp>
#include <mnp/tower.hpp>
#include <mnp/uiElements.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Clock clock;

    UIHandler *myUI = new UIHandler();
    UIComponent rootUI = new UIComponent(new Rectangle(0,0,1280,720));
    myUI.bindRootUI(rootUI);


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





        window.display();
    }

    return 0;
}

