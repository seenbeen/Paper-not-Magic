#include <mnp/tower.hpp>
#include <iostream>

Tower::Tower(int x, int y) :
            m_x(x), m_y(y) {
    std::cout << "hello constructor" << std::endl;
}

Tower::~Tower() {
    std::cout << "hello destructor" << std::endl;
}


SpecialTower::SpecialTower() :
                        Tower(69, 69) {
    std::cout << "hello special constructor" << std::endl;
}

SpecialTower::~SpecialTower() {
    std::cout << "hello special destructor" << std::endl;
}

void SpecialTower::doSomething() {
    std::cout << "I've done something" << std::endl;
}


NotSpecialTower::NotSpecialTower() :
                                Tower(12, 12){
    std::cout << "hello notspecial constructor" << std::endl;
}

NotSpecialTower::~NotSpecialTower() {
    std::cout << "hello notspecial destructor" << std::endl;
}

void NotSpecialTower::doSomething() {
    std::cout << "meep" << std::endl;
}

MyDude::MyDude(float px, float py, float r) :
                m_x(px), m_y(py), m_r(r), m_shape(r) {
    m_shape.setFillColor(sf::Color::Green);
}

MyDude::~MyDude() {}

void MyDude::update(sf::Time &dt, sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i v = sf::Mouse::getPosition(window);
        m_x = v.x - m_r;
        m_y = v.y - m_r;
    }
    m_x += dt.asSeconds() * 35.0f;
    m_y += dt.asSeconds() * 35.0f;
    m_shape.setPosition(m_x, m_y);
}

void MyDude::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}
