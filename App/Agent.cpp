//
// Created by ofirt on 19/06/2023.
//

#include "Agent.h"

#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>

Agent::Agent(std::string n, float x, float y, int h, int s) :
        SimObject(std::move(n),x,y), health(h), state("stopped"), destination(), speed(s), tasks(){

}

int Agent::getHealth() const {
    return health;
}

std::string Agent::getState() const {
    return state;
}

Point Agent::getDest() const {
    return destination;
}

int Agent::getSpeed() const {
    return speed;
}

void Agent::setHealth(int h) {
    /// the function add or decrease the health by the argument h
    /// to add enter positive number, to  decrease enter negative number
    health += h;
    if (health <= 0)
        state = "died";
}

void Agent::setState(const std::string& st) {
    state = st;
}

void Agent::setDest(float x, float y) {
    destination.setX(x);
    destination.setY(y);
}

void Agent::setSpeed(int s) {
    speed = s;
}

void Agent::printStatus() {
    std::cout << className()  << " " << getName() << " at (" << getLocation().getX() << ", "
    << getLocation().getY() << "), " << getState() << std::endl;
}

void Agent::insertCommand(const Task& c) {
    tasks.push_back(c);
}

void Agent::clearCommands() {
    tasks.clear();
    if(getState() != "died")
        setState("stopped");
}

std::vector<Task>& Agent::getTasks() {
    return tasks;
}

// Move the agent towards its current course (angle) and update the state.
void Agent::course() {
    getLocation().moveByAngle(getTasks()[0].getAngle(), speed);
    std::ostringstream oss;
    oss << getTasks()[0].getAngle();
    std::string result = oss.str();
    setState("Heading on course " + result +
    ", speed "  + std::to_string(speed) + " km/h" );
}

// Move the agent towards its current destination position and update the state.
void Agent::position() {
    if(getLocation().distanceTo(getTasks()[0].getPosition()) <= speed){
        getLocation().setX(getTasks()[0].getPosition().getX());
        getLocation().setY(getTasks()[0].getPosition().getY());
        getTasks().erase(getTasks().begin());
        return;
    }
    float angle = getLocation().calculateAngle(getTasks()[0].getPosition());
    getLocation().moveByAngle(angle, speed);
}

