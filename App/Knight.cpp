//
// Created by ofirt on 19/06/2023.
//

#include "Knight.h"
#include "Structure.h"

#include <utility>
#include <memory>
#include <algorithm>

Knight::Knight(std::string n, const std::shared_ptr<Structure>& ps) : Agent(std::move(n), ps->getLocation().getX(),
                                                                    ps->getLocation().getY(), 1, 10), st_list() {
    st_list.push_back(ps);
}


void Knight::update() {
    // Update function for the Knight agent.
    // This function is called periodically to execute the next task in the task list, if any.
    // The function checks the type of the next task and calls the corresponding function (course, position, or destination).
    if(getTasks().empty())
        return;
    if(getTasks()[0].getName() == "course"){
        course();
    }else if(getTasks()[0].getName() == "position"){
        position();
    }else if(getTasks()[0].getName() == "destination"){
        destination();
    }
}

void Knight::destination() {
    // Function to handle the "destination" task for the Knight agent.
    // The Knight is expected to visit a series of structures (sites) in the order specified by st_list.
    // The function calculates the distance to the next structure and moves towards it, updating the Knight's state accordingly.
    // Once the Knight reaches the current destination, it either selects the next structure from the list or sets its state to "stopped" if the list is empty.
    if(st_list.size() == 1 + Model::getOBJ().getStructures().size() && getLocation().distanceTo(st_list.back()->getLocation()) == 0) {
        clearCommands();
        setState("stopped");
    }

    setState("go to " + st_list.back()->getName());
    if(getLocation().distanceTo(st_list.back()->getLocation()) == 0){
        if (auto s = nextTarget())
            st_list.push_back(s);
        else
            st_list.push_back(getTasks()[0].getTarget1());
    }else if(getLocation().distanceTo(st_list.back()->getLocation()) < (float)getSpeed()) {
        getLocation().setX(st_list.back()->getLocation().getX());
        getLocation().setY(st_list.back()->getLocation().getY());
    } else{
        float angle = getLocation().calculateAngle(st_list.back()->getLocation());
        getLocation().moveByAngle(angle,getSpeed());
    }
}

void Knight::clearList() {
    st_list.clear();
}

void Knight::addToList(const std::shared_ptr<Structure>& s) {
    st_list.push_back(s);
}

std::shared_ptr<Structure> Knight::nextTarget() {  
    // Function to find the next target structure for the Knight to visit based on the current location and the available structures in the simulation.
    // The function calculates the distance between the Knight and all available structures and returns the closest structure that is not already in st_list.
    auto sts= Model::getOBJ().getStructures();

    std::sort(sts.begin(), sts.end(), [&](const std::shared_ptr<Structure>& p1,
                                          const std::shared_ptr<Structure>& p2) {
        return Point::distance(getLocation(), p1->getLocation()) < Point::distance(getLocation(), p2->getLocation());
    });

    bool flag = false;
    std::shared_ptr<Structure> next_target;
    for (auto s: sts) {
        flag = false;
        for(auto v: st_list){
            if(s->getName() == s->getName()){
                flag = true;
            }
        }
        if(!flag){
            return s;
        }
    }
    return nullptr;
}
