//
// Created by Sarah McLaughlin on 4/5/18.
//

#include "graphics.h"
#include "shapes.h"
#include <cmath>

/******************** point struct ********************/

point::point() : x(0), y(0) { }

point::point(int xIn, int yIn) : x(xIn), y(yIn) { }

point::point(double xIn, double yIn) {
    x = int(xIn);
    y = int(yIn);
}

double distance(const point &p1, const point &p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

/******************** direction struct ********************/

direction::direction() : xChange(0), yChange(0) { }

direction::direction(int xIn, int yIn) : xChange(xIn), yChange(yIn) { }

direction::direction(double xIn, double yIn) {
    xChange = int(xIn);
    yChange = int(yIn);
}

/******************** Shape class ********************/

Shape::Shape() : area(0), perimeter(0), center({0, 0}),
                 fill({0, 0, 0}), border({0, 0, 0}), dir({0, 0}) {
    // color defaults to black
}

Shape::Shape(point c, color b, color f, direction d) : area(0), perimeter(0),
                                                       center(c),
                                                       border(b), fill(f), dir(d){ }

Shape::Shape(int xIn, int yIn, int xChange, int yChange,
             double rb, double gb, double bb,
             double rf, double gf, double bf) : area(0),
                                                perimeter(0),
                                                center({xIn, yIn}),
                                                border({rb, gb, bb}),
                                                fill({rf, gf, bf}),
                                                dir({xChange, yChange}) { }

point Shape::getCenter() const {
    return center;
}

color Shape::getBorderColor() const {
    return border;
}

color Shape::getFillColor() const {
    return fill;
}

double Shape::getArea() const {
    return area;
}

double Shape::getPerimeter() const {
    return perimeter;
}

direction Shape::getDirection() const {
    return dir;
}

int Shape::getDirectionX() const{
    return dir.xChange;
}

int Shape::getDirectionY() const{
    return dir.yChange;
}

void Shape::setCenter(point c) {
    center = c;
}

void Shape::setCenter(int xIn, int yIn) {
    center = {xIn, yIn};
}

void Shape::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Shape::setBorderColor(color b) {
    border = b;
}

void Shape::setBorderColor(double r, double g, double b) {
    border = {r, g, b};
}

void Shape::setFillColor(color f) {
    fill = f;
}

void Shape::setFillColor(double r, double g, double b) {
    fill = {r, g, b};
}

void Shape::setDirection(direction d){
    dir = d;
}

void Shape::setDirection(int xChange, int yChange){
    dir = direction({xChange, yChange});
}

/******************** Circle class ********************/

void Circle::calculateArea() {
    area = PI * radius * radius;
}

void Circle::calculatePerimeter() {
    perimeter = 2.0 * PI * radius;
}

Circle::Circle() : Shape(), radius(0) { }

Circle::Circle(double rad) : Shape() {
    setRadius(rad);
}

Circle::Circle(color b, color f) : Shape({0, 0}, b, f, {0, 0}), radius(0) { }

Circle::Circle(double rb, double gb, double bb,
               double rf, double gf, double bf) :
        Shape(0, 0, 0, 0, rb, gb, bb, rf, gf, bf), radius(0) {}

Circle::Circle(double rad, color b, color f)  {
    // example without initializer list
    setCenter({0, 0});
    setBorderColor(b);
    setFillColor(f);
    setRadius(rad);
    calculateArea();
    calculatePerimeter();
}

Circle::Circle(double rad,
               double rb, double gb, double bb,
               double rf, double gf, double bf) :
        Shape(0, 0, 0, 0, rb, gb, bb, rf, gf, bf) {
    setRadius(rad);
}

Circle::Circle(double rad, point c) :
        Shape(c, {0, 0, 0}, {0, 0, 0}, {0, 0}) {
    setRadius(rad);
}

Circle::Circle(double rad, int xIn, int yIn) :
        Shape(xIn, yIn, 0, 0, 0, 0, 0, 0, 0, 0) {
    setRadius(rad);
}

Circle::Circle(double rad, int xIn, int yIn, int xChange, int yChange) :
        Shape(xIn, yIn, xChange, yChange, 0, 0, 0, 0, 0, 0) {
    setRadius(rad);
}

Circle::Circle(double rad, color b, color f, point c, direction d) :
        Shape(c, b, f, d) {
    setRadius(rad);
}

Circle::Circle(double rad,
               double rb, double gb, double bb,
               double rf, double gf, double bf,
               int xIn, int yIn, int xChange, int yChange) :
        Shape(xIn, yIn, xChange, yChange, rb, gb, bb, rf, gf, bf) {
    setRadius(rad);
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double rad) {
    // do not want to accept negative values for radius
    radius = (rad < 0) ? 0 : rad;
    calculateArea();
    calculatePerimeter();
}

void Circle::draw() const {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2i(center.x, center.y);
    glColor3f(border.red, border.green, border.blue);
    for (double i = 0; i < 2.0*PI+0.05; i += 2.0*PI/360.0) {
        glVertex2i(center.x + radius * cos(i),
                   center.y + radius * sin(i));
    }
    glEnd();
}

char Circle::getType() const {
    return 'c';
}

bool Circle::isOverlapping(const point &p) const {
    return distance(p, center) <= radius;
}

bool Circle::isOverlappingCircle(const Circle &c) const {
    return distance(center, c.center) <= radius + c.radius;
}

bool Circle::isOverlappingLineSeg(const point &p1, const point &p2) const {
    if (p1.x == p2.x) {
        // vertical line
        if (p1.x >= center.x-radius && p1.x <= center.x+radius) {
            if ((p1.y < center.y && p2.y > center.y) ||
                (p1.y > center.y && p2.y < center.y)) {
                return true;
            }
        }
        return false;
    }
    if (p1.y == p2.y) {
        // horizontal line
        if (p1.y >= center.y-radius && p1.y <= center.y+radius) {
            if ((p1.x < center.x && p2.x > center.x) ||
                (p1.x > center.x && p2.x < center.x)) {
                return true;
            }
        }
        return false;
    }
    return false;
}

/******************** Tangle class ********************/

void Tangle::calculateArea() {
    area = length * width;
}

void Tangle::calculatePerimeter() {
    perimeter = 2.0 * length + 2.0 * width;
}

Tangle::Tangle() : Shape(), length(0), width(0) { }

Tangle::Tangle(double l, double w) : Shape() {
    setDimensions(l, w);
}

Tangle::Tangle(double l, double w, color b, color f, point c, direction d) : Shape(c, b, f, d) {
    setDimensions(l, w);
}

double Tangle::getLength() const {
    return length;
}

double Tangle::getWidth() const {
    return width;
}

void Tangle::setDimensions(double l, double w) {
    // we don't want to accept negative values for length and width
    length = (l < 0) ? 0 : l;
    width = (w < 0) ? 0 : w;
    // update area and perimeter
    calculateArea();
    calculatePerimeter();
}

void Tangle::draw() const {
    // draw fill
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    // top right
    glVertex2i(center.x+(width/2.0), center.y-(length/2.0));
    // bottom right
    glVertex2i(center.x+(width/2.0), center.y+(length/2.0));
    // bottom left
    glVertex2i(center.x-(width/2.0), center.y+(length/2.0));
    glEnd();

    glLineWidth((GLfloat)5.0);
    // draw border
    glColor3f(border.red, border.green, border.blue);
    glBegin(GL_LINE_STRIP);
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    // top right
    glVertex2i(center.x+(width/2.0), center.y-(length/2.0));
    // bottom right
    glVertex2i(center.x+(width/2.0), center.y+(length/2.0));
    // bottom left
    glVertex2i(center.x-(width/2.0), center.y+(length/2.0));
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    glEnd();
}

char Tangle::getType() const {
    return 't';
}

bool Tangle::isOverlapping(const point &p) const {
    return (p.x >= center.x-(width/2.0) && // left side
            p.x <= center.x+(width/2.0) && // right side
            p.y >= center.y-(length/2.0) && // top
            p.y <= center.y+(length/2.0)); // bottom
}

bool Tangle::isOverlappingTangle(const Tangle &rectangle) const {
    return !(center.x+(width/2.0) < rectangle.center.x-(rectangle.width/2.0) || // self is left of rectangle
             rectangle.center.x+(rectangle.width/2.0) < center.x-(width/2.0) || // rectangle is left of self
             center.y-(length/2.0) > rectangle.center.y+(rectangle.length/2.0) || // self is below rectangle
             rectangle.center.y-(rectangle.length/2.0) > center.y+(length/2.0)); // rectangle is below self
}

bool isOverlappingTangleCircle(const Tangle &t, const Circle &c) {
    // either the circle's center is inside the rectangle
    // or one of the edges of the rectangle intersects the circle
    // #ThanksStackOverflow

    // check if center of circle is in rectangle
    if (t.isOverlapping(c.getCenter())) {
        return true;
    }

    // check if any rectangle corner is in circle
    if (c.isOverlapping({t.getCenter().x+t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0}) ||
        c.isOverlapping({t.getCenter().x+t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0}) ||
        c.isOverlapping({t.getCenter().x-t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0}) ||
        c.isOverlapping({t.getCenter().x-t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0})) {
        return true;
    }

    // check top edge of rectangle
    if (c.isOverlappingLineSeg({t.getCenter().x-t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0},
                               {t.getCenter().x+t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0})) {
        return true;
    }

    // check bottom edge of rectangle
    if (c.isOverlappingLineSeg({t.getCenter().x-t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0},
                               {t.getCenter().x+t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0})) {
        return true;
    }

    // check left edge of rectangle
    if (c.isOverlappingLineSeg({t.getCenter().x-t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0},
                               {t.getCenter().x-t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0})) {
        return true;
    }

    // check right edge of rectangle
    if (c.isOverlappingLineSeg({t.getCenter().x+t.getWidth()/2.0, t.getCenter().y+t.getLength()/2.0},
                               {t.getCenter().x+t.getWidth()/2.0, t.getCenter().y-t.getLength()/2.0})) {
        return true;
    }

    return false;
}

bool isOverlappingTangle(const std::unique_ptr<Shape> &s, const Tangle &r) {
    if (s->getType() == 't') {
        return r.isOverlappingTangle(dynamic_cast<Tangle&>(*s));
    } else {
        return isOverlappingTangleCircle(r, dynamic_cast<Circle&>(*s));
    }
}
