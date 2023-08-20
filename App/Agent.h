//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_AGENT_H
#define EX3_AGENT_H

#include <vector>
#include "SimObject.h"
#include "Task.h"

class Agent : public SimObject{
private:
    int health;
    std::string state;
    Point destination;
    int speed;
    std::vector<Task> tasks;
public:
    Agent(std::string, float, float, int, int);
    void start_moving();
    void printStatus() override;
    int getHealth() const;
    void setHealth(int);
    std::string getState() const;
    void setState(const std::string&);

    Point getDest() const;
    void setDest(float x, float y);

    int getSpeed() const;
    void setSpeed(int);

    void insertCommand(const Task &c);
    void clearCommands();

    std::vector<Task>& getTasks();

    void course();
    void position();
};


#endif //EX3_AGENT_H
