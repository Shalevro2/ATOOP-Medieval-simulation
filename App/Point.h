//
// Created by ofirt on 11/06/2023.
//

#ifndef EX3_POINT_H
#define EX3_POINT_H

#include <cmath>

#define CUBE_SIZE 10

class Point {
public:
    // Default constructor
    Point() : x(0.0f), y(0.0f) {}

    // Parameterized constructor
    Point(float xPos, float yPos) : x(xPos), y(yPos) {}

    // Getter methods
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    // Setter methods
    void setX(float xPos) {
        x = xPos;
        if(x < 0.00001)
            x = 0;
    }

    void setY(float yPos) {
        y = yPos;
        if(y < 0.00001)
            y = 0;
    }

    // Calculate distance between two points
    float distanceTo(const Point& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy)*CUBE_SIZE;
    }

    float calculateAngle(const Point& other) const {
        float dx = other.x - x;
        float dy = other.y - y;
        return float(std::atan2(dy, dx) * 180.0 / M_PI);
    }

    void moveByAngle(float angle, int hypotenuse) {
        float angleInRadians = static_cast<float>(angle * M_PI) / 180.0f;
        float dx = float(hypotenuse) * std::cos(angleInRadians);
        float dy = float(hypotenuse) * std::sin(angleInRadians);
        x += dx/CUBE_SIZE;
        y += dy/CUBE_SIZE;
        if(x < 0.00001)
            x = 0;
        if(y < 0.00001)
            y = 0;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Euclidean distance between two points
    static double distance(const Point& p1, const Point& p2) {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        return std::sqrt(dx*dx + dy*dy);
    }
private:
    float x; // x coordinate
    float y; // y coordinate
};



#endif //EX3_POINT_H
