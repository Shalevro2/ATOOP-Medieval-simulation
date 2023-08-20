#ifndef EX3_TASK_H
#define EX3_TASK_H

#include <utility>
#include "Point.h"
#include "Structure.h"
//#include "Agent.h"
#include <memory>
//#include "Peasant.h"

class Agent;

class Task {
private:
    std::string name;
    float angle;
    Point position;
    std::shared_ptr<Structure> target1;
    std::shared_ptr<Structure> target2;
    std::shared_ptr<Agent> attack;
    std::string status;

public:
    Task(std::string n) : name(std::move(n)), angle(), position(), target1(), target2(), attack(), status() {

    }

    // Getters
    float getAngle() const {
        return angle;
    }

    Point getPosition() const {
        return position;
    }

    std::shared_ptr<Structure> getTarget1() const {
        return target1;
    }

    std::shared_ptr<Structure> getTarget2() const {
        return target2;
    }

    std::shared_ptr<Agent> getAttack() const {
        return attack;
    }

    std::string getStatus() const {
        return status;
    }

    std::string getName() const {
        return name;
    }

    // Setters
    void setAngle(float newAngle) {
        angle = newAngle;
    }

    void setPosition(const Point& newPosition) {
        position.setY(newPosition.getY());
        position.setX(newPosition.getX());
    }

    void setTarget1(const std::shared_ptr<Structure>& newTarget1) {
        target1 = newTarget1;
    }

    void setTarget2(const std::shared_ptr<Structure>& newTarget2) {
        target2 = newTarget2;
    }

    void setAttack(const std::shared_ptr<Agent>& newAttack) {
        attack = newAttack;
    }

    void setStatus(const std::string& newStatus) {
        status = newStatus;
    }
};

#endif //EX3_TASK_H