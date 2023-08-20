//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_THUG_H
#define EX3_THUG_H


#include "Agent.h"

class Thug : public Agent{
public:
    Thug(std::string, float, float);
    void update() override;
    std::string className() const override { return "Thug"; }
    void attack();
};


#endif //EX3_THUG_H
