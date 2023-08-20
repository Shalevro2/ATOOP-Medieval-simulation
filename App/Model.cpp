//
// Created by ofirt on 19/06/2023.
//

#include "Model.h"
#include "Farm.h"
#include "Peasant.h"
#include "Thug.h"
#include <utility>
#include <algorithm>
#include "Knight.h"

Model *Model::obj = nullptr;

void Model::addCastle(const std::string& n, float x, float y, int a) {
    std::shared_ptr<Castle> p1(new Castle(n,x,y,a));
    st_list.push_back(p1);
}

void Model::addFarm(const std::string &n, float x, float y, int a, int r) {
    std::shared_ptr<Farm> p1(new Farm(n,x,y,a, r));
    st_list.push_back(p1);
}

// Function to create a new agent with the specified name, type (Peasant or Thug), and coordinates.
// Checks if an agent with the given name already exists and if the name length is valid.
void Model::createAgent(std::string name, const std::string& type, float x, float y) {
    std::shared_ptr<Agent> p2(getAgent(name));
    if (p2.get()){
        std::cerr << "this name agent already exist" << std::endl;
        return;
    }

    if(name.size() > 16){
        std::cerr << "name too long" << std::endl;
        return;
    }

    if  (type == "Peasant"){
        std::shared_ptr<Peasant> p1(new Peasant(std::move(name),x,y));
        ag_list.push_back(p1);
    } else if (type == "Thug"){
        std::shared_ptr<Thug> p1(new Thug(std::move(name),x,y));
        ag_list.push_back(p1);
    }else
        std::cerr << "wrong type of Agent" << std::endl;
}

std::shared_ptr<Agent> Model::getAgent(const std::string& name) {
    for (const std::shared_ptr<Agent>& a : ag_list){
        if (a->getName() == name)
            return a;
    }
    return nullptr;
}

// Function to create a new Knight agent with the specified name and assign it to a target structure.
// Checks if an agent with the given name already exists, if the target structure exists, and if the name length is valid.
void Model::createAgent(const std::string& name, const std::string& site) {
    std::shared_ptr<Agent> p2(getAgent(name));
    if (p2.get()){
        std::cerr << "this name agent already exist" << std::endl;
        return;
    }

    std::shared_ptr<Structure> p3(getStructure(site));
    if (!p3.get()){
        std::cerr << "this site not exist" << std::endl;
        return;
    }

    if(name.size() > 16){
        std::cerr << "name too long" << std::endl;
        return;
    }

    std::shared_ptr<Agent> p1(new Knight(name,p3));
    ag_list.push_back(p1);
}

std::shared_ptr<Structure> Model::getStructure(const std::string &name) {
    for (const std::shared_ptr<Structure>& s : st_list){
        if (s->getName() == name)
            return s;
    }
    return nullptr;
}

void Model::printStatus() {
    for(const std::shared_ptr<Structure>& ps : st_list)
        ps->printStatus();
    for(const std::shared_ptr<Agent>& pa : ag_list)
        pa->printStatus();
}

// Function that advances the simulation by one time step.
// Calls the update function for all structures and agents and increments the time counter.
void Model::go() {
    for(const std::shared_ptr<Structure>& ps : st_list)
        ps->update();
    for(const std::shared_ptr<Agent>& pa : ag_list)
        pa->update();
    time += 1;
}

// Function to search for a structure or agent within a specific point and scale in the simulation.
// Returns the name of the found structure or agent, or an empty string if nothing is found.
std::string Model::searchInPoint(float x, float y, float scale) {
    for (std::shared_ptr<Structure> ps : st_list) {
        if(ps->getLocation().getX() <= x+scale/2 && ps->getLocation().getX() >= x-scale/2 &&
                ps->getLocation().getY() <= y+scale/2 && ps->getLocation().getY() >= y-scale/2 )
            return ps->getName();
    }

    for (std::shared_ptr<Agent> pa : ag_list) {
        if(pa->getLocation().getX() <= x+scale/2 && pa->getLocation().getX() >= x-scale/2 &&
           pa->getLocation().getY() <= y+scale/2 && pa->getLocation().getY() >= y-scale/2 )
            return pa->getName();
    }
    return "";
}

// Function to search for a Knight agent within a specific radius around a given agent.
// Returns true if a Knight agent is found within the radius, false otherwise.
bool Model::searchKnightInRadius(const std::shared_ptr<Agent>& ps) {
    return std::any_of(ag_list.begin(), ag_list.end(), [&](const std::shared_ptr<Agent>& a) {
        return a->className() == "Knight" && ps->getLocation().distanceTo(a->getLocation()) <= 2.5;
    });
}

