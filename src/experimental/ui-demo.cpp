#include <iostream>
#include <SFML/Graphics.hpp>
#include <engine/input/input-system.hpp>
#include <experimental/ui-demo.hpp>



int UIDemo::run()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Clock clock;


    MNPInput::InputHandler* t = new MNPInput::InputHandler();

    UIHandler *myUI = new UIHandler(t);


    //BlankContext* rootcontext = new BlankContext();
    UIRoot *rootUI = new UIRoot(0,0,1280,720,new BlankContext());
    myUI->bindRootUI(rootUI);


    //UIClickableContext* button1context = new UIClickableContext();
    UIButton *myButton = new UIButton(50,50,100,100,new UIClickableContext());
    rootUI->addComponent(myButton);


    UIButton *myButton2 = new UIButton(70,70,100,100,new UIClickableContext());
    rootUI->addComponent(myButton2);

    //UITextInputBox *myinput = new UITextInputBox(0,0,100,100,3);
    //rootUI->addComponent(myinput);
    myButton2->changeColor(sf::Color(255,255,255));



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            t->sendEvent(&event);
            //myUI->sendEvent(&event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        window.clear();

        myUI->update(elapsed);
        myUI->render(window);

        t->update(elapsed);

        window.display();
    }
    return 0;
};
