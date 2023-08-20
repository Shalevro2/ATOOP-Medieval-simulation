//
// Created by ofirt on 19/06/2023.
//

#include "Peasant.h"
#include "Farm.h"

#include <utility>

Peasant::Peasant(std::string n, float x, float y) : Agent(std::move(n), x, y, 10, 5), carry(0){

}

int Peasant::getCarry() const {
    return carry;
}

void Peasant::setCarry(int c) {
    carry = c;
}

// Function to update the state and behavior of the Peasant agent based on its current task.
void Peasant::update() {
    if (getTasks().empty() || getState() == "died")
        return;
    if (getTasks()[0].getStatus() == "stopped") {
        setState("Moving To " + getTasks()[0].getTarget1()->getName());
        auto p = getTasks()[0].getTarget1()->getLocation();
        float dis = getLocation().distanceTo(p);
        if (dis <= (float)getSpeed())
            setLocation(p);
        else{
            getLocation().moveByAngle(getLocation().calculateAngle(p),getSpeed());
        }

        if (getLocation() == getTasks()[0].getTarget1()->getLocation())
            getTasks()[0].setStatus("load");
        else
            getTasks()[0].setStatus("way_go");

    } else if(getTasks()[0].getStatus() == "way_go"){
        if (getLocation() == getTasks()[0].getTarget1()->getLocation())
            getTasks()[0].setStatus("load");
        else {
            auto p = getTasks()[0].getTarget1()->getLocation();
            getLocation().moveByAngle(getLocation().calculateAngle(p), getSpeed());
        }
    } else if (getTasks()[0].getStatus() == "load"){
        setState("Moving To " + getTasks()[0].getTarget2()->getName());
        if (getTasks()[0].getTarget1()->getAmount() > 5){
            setCarry(5);
            getTasks()[0].getTarget1()->setAmount(-5);
        }
        else{
            setCarry(getTasks()[0].getTarget1()->getAmount());
            getTasks()[0].getTarget1()->makeEmpty();
        }

        if (getLocation() == getTasks()[0].getTarget2()->getLocation())
            getTasks()[0].setStatus("unload");
        else
            getTasks()[0].setStatus("way_back");

    } else if(getTasks()[0].getStatus() == "way_back"){

        auto p = getTasks()[0].getTarget2()->getLocation();
        float dis = getLocation().distanceTo(p);
        if (dis <= (float)getSpeed()) {
            setLocation(p);
            getTasks()[0].setStatus("unload");
        }
        else{
            getLocation().moveByAngle(getLocation().calculateAngle(p),getSpeed());
        }

    } else if (getTasks()[0].getStatus() == "unload"){
        getTasks()[0].setStatus("finish");
        setHealth(1);
        getTasks()[0].getTarget2()->setAmount(getCarry());
        setCarry(0);
        getTasks().erase(getTasks().begin());
        setState("stopped");

    }
}
