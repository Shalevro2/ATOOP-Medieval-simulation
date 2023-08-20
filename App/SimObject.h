//
// Created by ofirt on 11/06/2023.
//

#ifndef EX3_SIMOBJECT_H
#define EX3_SIMOBJECT_H

#include <string>
#include "Point.h"

class SimObject {
private:
    std::string name;
    Point location;
public:
    SimObject(std::string, float, float );
    virtual void printStatus() = 0;
    virtual void update() = 0;
    virtual std::string className() const = 0;
    std::string getName();
    Point& getLocation();
    void setLocation(Point);
};


#endif //EX3_SIMOBJECT_H
