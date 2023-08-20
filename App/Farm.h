//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_FARM_H
#define EX3_FARM_H

#include "Structure.h"

class Farm : public Structure{
private:
    int rate;
public:
    Farm(std::string, float, float, int, int);

    void update() override;
    std::string className() const override { return "Farm"; }


};


#endif //EX3_FARM_H
