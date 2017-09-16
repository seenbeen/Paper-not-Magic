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
