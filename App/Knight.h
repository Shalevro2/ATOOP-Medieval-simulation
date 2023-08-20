//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_KNIGHT_H
#define EX3_KNIGHT_H


#include <memory>
#include "Agent.h"
#include "Structure.h"
#include <vector>
#include "Model.h"

class Knight : public Agent{
private:
    std::vector<std::shared_ptr<Structure>> st_list;
    std::shared_ptr<Structure> nextTarget();
public:

    Knight(std::string n, const std::shared_ptr<Structure> &ps);
    std::string className() const override { return "Knight"; }

    void update() override;
    void destination();
    void clearList();
    void addToList(const std::shared_ptr<Structure>&);
};


#endif //EX3_KNIGHT_H
