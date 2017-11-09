#include <mnp/framework/ui/shapes.hpp>

Point::Point(int x, int y) : m_x(x), m_y(y){}
Point::~Point(){}

Rectangle::Rectangle(int x,int y,int l, int h) : m_x(x),m_y(y),m_l(l),m_h(h) {}
Rectangle::~Rectangle(){}

Rectangle::Rectangle() : m_x(0),m_y(0),m_l(0),m_h(0) {}

sf::RectangleShape *Rectangle::createShape() {
    return new sf::RectangleShape(sf::Vector2f(m_h, m_l));
}
sf::Vector2f Rectangle::getSize() {

    return sf::Vector2f(m_l,m_h);
}

void Point::getCoord(int &x, int &y){

    x=m_x;
    y=m_y;

}

void Point::addOffset(int x,int y){

    m_x+=x;
    m_y+=y;

}

void Rectangle::getCoord(int &x, int &y){

    x=m_x;
    y=m_y;

}

bool Rectangle::collide(int x, int y){

    if (m_x <= x && (m_x+m_l) >= x){

        if (m_y <= y && (m_y+m_h) >= y){

            return true;
        }
    }
    return false;


}


Line::Line(Point start,Point param_end) : m_start(start), m_end(param_end) {};
Line::~Line(){};
