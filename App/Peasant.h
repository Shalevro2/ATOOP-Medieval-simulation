//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_PEASANT_H
#define EX3_PEASANT_H


#include "Agent.h"

class Peasant : public Agent{
private:
    int carry;
public:
    Peasant(std::string, float, float);

    int getCarry() const;
    void setCarry(int);
    void update() override;
    std::string className() const override { return "Peasant"; }

};


#endif //EX3_PEASANT_H
