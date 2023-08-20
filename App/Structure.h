//
// Created by ofirt on 11/06/2023.
//

#ifndef EX3_STRUCTURE_H
#define EX3_STRUCTURE_H

#include "SimObject.h"

class Structure: public SimObject{
private:
    int amount;
public:
    Structure(std::string, float, float, int);
    void printStatus() override;
    int getAmount() const;
    void setAmount(int);
    void makeEmpty();
};


#endif //EX3_STRUCTURE_H
