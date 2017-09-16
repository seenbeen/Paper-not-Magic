#pragma once

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
