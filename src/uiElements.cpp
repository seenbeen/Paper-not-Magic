#include <mnp/uiElements.hpp>

Point::Point(int x, int y) : m_x(x), m_y(y){



};

Rectangle::Rectangle(Point topL, Point bottomR) : m_topL(topL), m_bottomR(bottomR){


};


Line::Line(Point start,Point param_end) : m_start(start), m_end(param_end) {
};
