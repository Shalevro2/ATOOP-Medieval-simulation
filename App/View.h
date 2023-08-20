//
// Created by ofirt on 22/06/2023.
//

#ifndef EX3_VIEW_H
#define EX3_VIEW_H

#include "Point.h"
#include "iostream"
#include "Model.h"

class View {
private:
    int size;
    float scale;
    Point origin;
public:
    View();

    // Getters
    int getSize() const {
        return size;
    }

    float getScale() const {
        return scale;
    }

    Point getOrigin() const {
        return origin;
    }

    // Setters
    void setSize(int newSize) {
        size = newSize;
    }

    void setScale(float newScale) {
        scale = newScale;
    }

    void setOrigin(const Point& newOrigin) {
        origin = newOrigin;
    }

    void show();

    void default_handler();


};


#endif //EX3_VIEW_H
