#pragma once
#include <SFML/Graphics.hpp>

class Tower {
    int m_x, m_y;

public:
    Tower(int x, int y);
    virtual ~Tower();

    virtual void doSomething() = 0;
};

class SpecialTower : public Tower {
public:
    SpecialTower();
    ~SpecialTower();

    void doSomething();
};

class NotSpecialTower : public Tower {
public:
    NotSpecialTower();
    ~NotSpecialTower();

    void doSomething();
};

class MyDude {
    float m_x, m_y, m_r;
    sf::CircleShape m_shape;
public:
    MyDude(float px, float py, float r);
    ~MyDude();

    void update(sf::Time &dt, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};
