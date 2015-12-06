#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "gwindow.h"

#define FRACTAL_PIXEL_SIZE 0.1
#define MATH_PI 3.141592

using namespace std;

class SierpinskiTriangleDrawer {

private:
    GWindow * _canvas;
    vector<GPoint> _vertex;
    std::mt19937 *eng;
    std::uniform_int_distribution<>* distr;


public:

    // constructor of object
    // generates GWindow obj
    SierpinskiTriangleDrawer(double window_W, double window_H) {

        // hardware random number generating seeding and limiting
        std::random_device rd; // obtain a random number from hardware
        eng = new std::mt19937(rd()); // seed the generator
        distr = new std::uniform_int_distribution<>(0, 2); // define the range

        // creating a canvas
        _canvas = new GWindow(window_W, window_H);

        // calculating a vertex
        double midpoint_x = window_W / 2;
        double midpoint_y = window_H / 2;
        for (int i = 0; i < 3; ++i) {
            _vertex.push_back(GPoint(
                min(midpoint_y, midpoint_x) * 0.7 * cos(i*MATH_PI*2/3) + midpoint_x,
                min(midpoint_y, midpoint_x) * 0.7 * sin(i*MATH_PI*2/3) + midpoint_y
            ));
        }
    }

    // calculates position of middlepoint for 2 GPoint objects
    // returns new GPoint with calculated coordinates
    GPoint middlePoint(GPoint & p1, GPoint & p2) {
        int mid_x = (p1.getX()+p2.getX()) / 2;
        int mid_y = (p1.getY()+p2.getY()) / 2;
        return GPoint(mid_x, mid_y);
    }

    // draws GPoint to canvas as a rectangular (a small one ^^)
    void drawPoint(GPoint & point) {
        _canvas->drawRect(point.getX(), point.getY(), FRACTAL_PIXEL_SIZE, FRACTAL_PIXEL_SIZE);
    }

    // recursive function that draws fractal to canvas
    void drawFractal(GPoint & curr) {
        GPoint temp = middlePoint(curr, getRandomVertexPoint());
        drawPoint(temp);
        drawFractal(temp);
    }

    GPoint & getRandomVertexPoint() {
        return _vertex.at(distr->operator()(*eng));
    }

    ~SierpinskiTriangleDrawer() {
        _canvas->close();
        exitGraphics();
        delete _canvas;
    }
};

int main() {

    SierpinskiTriangleDrawer a(700, 100);
    a.drawFractal(a.getRandomVertexPoint());

    return 0;
}
