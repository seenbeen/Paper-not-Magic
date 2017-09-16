#pragma once

class Point {
    int m_x,m_y;
public:
    Point(int x,int y);
    ~Point();

};

class Rectangle {
    Point m_topL,m_bottomR;
public:
    Rectangle(Point topL, Point bottomR);
    ~Rectangle();


};

class Line {
    Point m_start,m_end;
public:
    Line (Point start,Point param_end);
    ~Line();

};
