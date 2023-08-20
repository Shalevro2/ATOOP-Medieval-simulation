//
// Created by ofirt on 19/06/2023.
//

#include "Thug.h"

#include <utility>
#include <iostream>
#include "Model.h"

Thug::Thug(std::string n, float x, float y) : Agent(std::move(n), x, y, 5, 0){

}

// Function to update the state and behavior of the Thug agent based on its current task.
void Thug::update() {

    if(getTasks().empty())
        return;
    if(getTasks()[0].getName() == "course"){
        course();
    }else if(getTasks()[0].getName() == "position"){
        position();
    }else if (getTasks()[0].getName() == "attack"){
        attack();
    }

}

// Function representing the attack behavior of the Thug agent, where it attacks a specified Peasant agent.
void Thug::attack() {

    auto ps = dynamic_cast<Peasant*> (getTasks()[0].getAttack().get());

    if (getLocation().distanceTo(ps->getLocation()) > 1){
        std::cout << "distance too long from Peasant" << std::endl;
        setHealth(-1);
        clearCommands();
        return;
    }

    ps->setHealth(-1);

    setLocation(ps->getLocation());
    setState("stopped");

    if(Model::getOBJ().searchKnightInRadius(getTasks()[0].getAttack())){
        std::cout << "There is Knight nearby" << std::endl;
        setHealth(-1);
        clearCommands();
        return;
    }

    if (getHealth() <= ps->getHealth()){
        std::cout << "Thug power is not stronger then Peasant" << std::endl;
        setHealth(-1);
        clearCommands();
        return;
    }

    ps->setCarry(0);
    ps->clearCommands();
    setHealth(1);



}

