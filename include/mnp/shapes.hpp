#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class Point {

public:
    int m_x,m_y;
    void getCoord(int &x, int &y);
    void addOffset(int x,int y);
    Point(int x,int y);
    ~Point();
};

class Rectangle {
    int m_x,m_y,m_l,m_h;
public:
    Rectangle(int x, int y, int l, int h);
    Rectangle();
    ~Rectangle();
    sf::RectangleShape* createShape();
    sf::Vector2f getSize();
    void getCoord(int &x, int &y);
    //bool collide(Point &p);
    bool collide(int x, int y);
};

class Line {
    Point m_start,m_end;
public:
    Line (Point start,Point param_end);
    ~Line();
};

