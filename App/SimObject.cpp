//
// Created by ofirt on 11/06/2023.
//

#include "SimObject.h"

#include <utility>

SimObject::SimObject(std::string n, float x, float y): name(std::move(n)), location(x,y) {

}

std::string SimObject::getName() {
    return name;
}

Point& SimObject::getLocation() {
    return location;
}

void SimObject::setLocation(Point p) {
    location = p;
}
