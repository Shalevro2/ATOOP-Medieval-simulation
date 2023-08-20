//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include <iostream>
#include <vector>
#include "Structure.h"
#include "Agent.h"
#include "Castle.h"
#include <memory>
#include "Peasant.h"

class Model{
private:
    static Model* obj;
    std::vector<std::shared_ptr<Structure>> st_list;
    std::vector<std::shared_ptr<Agent>> ag_list;
    int time;
    Model() : st_list(), ag_list(), time(0){}
public:
    static Model& getOBJ() {
        if (obj == nullptr) {
            obj = new Model();
        }
        return *obj;
    }

    int getTime() const { return time; }
    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;

    std::vector<std::shared_ptr<Structure>> getStructures() const { return st_list;}

    void addCastle(const std::string&, float, float, int);
    void addFarm(const std::string&, float, float, int, int);

    void createAgent(std::string, const std::string&, float, float );
    void createAgent(const std::string&, const std::string&);

    std::shared_ptr<Agent> getAgent(const std::string&);
    std::shared_ptr<Structure> getStructure(const std::string&);

    void printStatus();
    void go();

    std::string searchInPoint(float, float, float);

    bool searchKnightInRadius(const std::shared_ptr<Agent>&);
};



#endif //EX3_MODEL_H
