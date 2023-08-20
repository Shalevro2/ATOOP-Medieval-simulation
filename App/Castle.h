//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_CASTLE_H
#define EX3_CASTLE_H

#include "Structure.h"

class Castle : public Structure{
public:
    Castle(std::string, float, float, int);
    void update() override;

    std::string className() const override { return "Castle"; }
};


#endif //EX3_CASTLE_H
