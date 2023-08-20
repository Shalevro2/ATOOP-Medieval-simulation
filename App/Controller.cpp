//
// Created by ofirt on 19/06/2023.
//

#include <fstream>
#include <sstream>
#include "Controller.h"
#include "map"
#include "Thug.h"
#include "Task.h"
#include "Knight.h"

void Controller::run(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Illegal number of arguments" << std::endl;
        return;
    }

    if(!castles_file_handler(argv[1]) || !farms_file_handler(argv[2]))
        return;

    std::cout << "Time " << Model::getOBJ().getTime() << " : ";
    while (do_move()) {
        std::cout << "Time " << Model::getOBJ().getTime() << " : ";
    }
}

bool Controller::castles_file_handler(char* file_name) {
    // Function to read and handle the input file containing castle data.
    // The file format is expected to be as follows: "name (x,y), value"
    // If the file format is incorrect or invalid, it returns false; otherwise, it returns true.
    std::ifstream castles_file(file_name);
    if (!castles_file) {
        std::cerr << "Error opening/reading the specified file." << file_name << std::endl;
        return false;
    }

    try {
        std::string line;
        while(std::getline(castles_file, line)) {
            std::istringstream iss(line);
            std::string name;
            char comma1, comma2, openingParenthesis, closingParenthesis;
            float x, y;
            int value;

            if (iss >> name >> openingParenthesis >> x >> comma2 >> y >> closingParenthesis >> comma1 >> value) {
                if (openingParenthesis == '(' && comma2 == ',' && closingParenthesis == ')' && comma1 == ',' && name.back()==',' ) {
                    name.erase(name.size()-1);
                    Model::getOBJ().addCastle(name, x, y,value);
                }else {
                    std::cerr << "Invalid input in file " << file_name << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Invalid input in file " << file_name << std::endl;
                return false;
            }
        }
    }catch (...) {
        std::cerr << "Invalid input in file "<< file_name  << std::endl;
        return false;
    }
    return true;
}

bool Controller::farms_file_handler(char* file_name) {
    // Function to read and handle the input file containing farm data.
    // The file format is expected to be as follows: "name (x,y), value, rate"
    // If the file format is incorrect or invalid, it returns false; otherwise, it returns true.
    std::ifstream farms_file(file_name);
    if (!farms_file) {
        std::cerr << "Error opening/reading the specified file." << file_name << std::endl;
        return false;
    }

    try {
        std::string line;
        while(std::getline(farms_file, line)) {
            std::istringstream iss(line);
            std::string name;
            char comma1, comma2, openingParenthesis, closingParenthesis, comma3;
            float x, y;
            int value, rate;

            if (iss >> name >> openingParenthesis >> x >> comma2 >> y >> closingParenthesis >> comma1 >>
            value >> comma3 >> rate) {
                if (openingParenthesis == '(' && comma2 == ',' && closingParenthesis == ')' && comma1 == ',' &&
                comma3 == ',' && name.back()==',' ) {
                    name.erase(name.size()-1);
                    Model::getOBJ().addFarm(name, x, y,value, rate);
                }else {
                    std::cerr << "Invalid input in file " << file_name << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "Invalid input in file " << file_name << std::endl;
                return false;
            }
        }
    }catch (...) {
        std::cerr << "Invalid input in file "<< file_name  << std::endl;
        return false;
    }
    return true;
}

bool Controller::do_move() {
    // Function to process user commands during the simulation.
    // The user can issue various commands related to the simulation.
    // If the command is valid, the function performs the corresponding action.
    // If the command is invalid or not recognized, it prints an error message and continues with the next command.
    // The function returns true as long as the simulation should continue and false when the user issues an "exit" command.
    std::string input, command;
    std::map<std::string, int> first_command{
            {"exit", 1},
            {"default", 2},
            {"size", 3},
            {"zoom", 4},
            {"pan", 5},
            {"show", 6},
            {"status", 7},
            {"go", 8},
            {"create", 9},
    };
    std::getline(std::cin, input);
    std::istringstream iss(input);
    iss >> command;

    switch (first_command[command]) {
        case 1:
            return false;
        case 2:
            view.default_handler();
            return true;
        case 3:
            size_handler(input);
            return true;
        case 4:
            zoom_handler(input);
            return true;
        case 5:
            pan_handler(input);
            return true;
        case 6:
            view.show();
            return true;
        case 7:
            Model::getOBJ().printStatus();
            return true;
        case 8:
            Model::getOBJ().go();
            return true;
        case 9:
            create_handler(input);
            return true;
        default:
            default_handler(input);
            return true;
    }

}

void Controller::create_handler(const std::string& input) {
    // Function to handle the "create" command for creating new agents (characters) in the simulation.
    // The user can create different types of agents like "Knight" and "Peasant" with specific attributes.
    // If the command is valid, the function creates the agent and adds it to the simulation.
    // If the command is invalid or not recognized, it prints an error message and continues with the next command.
    std::string first, sec, thr, command;
    std::istringstream iss(input);
    iss >> command;
    try{
        if(iss >> first >> sec){
            if (first.size() <2  || first.size() >16) {
                std::cerr << "the name must be at range 2-16 characters" << std::endl;
            }
            if(sec == "Knight"){
                iss >> thr;
                Model::getOBJ().createAgent(first, thr);
            }
            else {
                char temp;
                float x, y;
                iss >> temp >> x >> temp >> y >> temp ;
                Model::getOBJ().createAgent(first, sec, x, y);
            }
        }else{
            std::cerr << "Illegal command" << std::endl;
        }
    }catch (...){
        std::cerr << "Illegal command" << std::endl;
    }
}

void Controller::default_handler(const std::string& input) {
    // Extract the agent name from the input and retrieve the corresponding agent from the simulation model.
    // If the agent is not found, print an error message and return.
    // Otherwise, determine the specific command type based on the input and delegate to the corresponding handler function.
    std::string name, command;
    std::istringstream iss(input);
    iss >> name;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    std::map<std::string, int> commands{
            {"course", 1},
            {"position", 2},
            {"destination", 3},
            {"stop", 4},
            {"attack", 5},
            {"start_working", 6},

    };
    iss >> command;

    switch (commands[command]) {
        case 1:
            course_handler(input);
            break;
        case 2:
            position_handler(input);
            break;
        case 3:
            destination_handler(input);
            break;
        case 4:
            stop_handler(input);
            break;
        case 5:
            attack_handler(input);
            break;
        case 6:
            start_working_handler(input);
            break;
        default:
            std::cerr << "Illegal command" << std::endl;
            break;
    }

}

void Controller::course_handler(const std::string &input) {
    // Extract the agent name and course angle from the input.
    // Retrieve the corresponding agent from the simulation model and validate its type.
    // If the agent is a peasant or not found, print an error message and return.
    // Otherwise, create a new task with the specified angle and speed (if provided), and insert it as the agent's new command.
    // Update the agent's state accordingly.
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa || pa->className() == "Peasant"){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }
    float angle;
    int speed;

    if (iss >> angle){
        pa->clearCommands();
        Task c(command_name);
        c.setAngle(angle);
        if (iss >> speed){
            Thug* t = dynamic_cast<Thug*>(pa.get());
            t->setSpeed(speed);
        }
        pa->insertCommand(c);
        pa->setState("Heading on course " + std::to_string(angle));
    }else{
        std::cerr << "Illegal command" << std::endl;
    }

}

void Controller::position_handler(const std::string &input) {
    // Extract the agent name and position from the input.
    // Retrieve the corresponding agent from the simulation model and validate its type.
    // If the agent is a peasant or not found, print an error message and return.
    // Otherwise, create a new task with the specified position and speed (if provided), and insert it as the agent's new command.
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa || pa->className() == "Peasant"){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }
    float x, y;
    int speed;
    char openingParenthesis, comma1, closingParenthesis;

    if (iss >> openingParenthesis >> x >> comma1 >> y >> closingParenthesis ){
        Task c(command_name);
        c.setPosition(Point(x, y));
        if (iss >> speed){
            Thug* t = dynamic_cast<Thug*>(pa.get());
            t->setSpeed(speed);
        }
        pa->clearCommands();
        pa->insertCommand(c);
    }else{
        std::cerr << "Illegal command" << std::endl;
    }
}

void Controller::destination_handler(const std::string &input) {
    // Extract the agent name and destination site name from the input.
    // Retrieve the corresponding agent from the simulation model and validate its type.
    // If the agent is not found or not a knight, print an error message and return.
    // Otherwise, retrieve the corresponding structure (site) from the simulation model using the site name.
    // If the structure is not found, print an error message and return.
    // Otherwise, create a new task with the destination as the target and insert it as the knight's new command.
    // Clear the knight's command list and update its state accordingly.
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    if(pa->className() != "Knight"){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    std::string site_name;

    if(iss >> site_name){
        std::shared_ptr<Structure> ps = Model::getOBJ().getStructure(site_name);
        if(!ps){
            std::cout << "Wrong site name or command" << std::endl;
            return;
        }
        Task c(command_name);
        auto* k = dynamic_cast<Knight*>(pa.get());
        k->clearList();
        k->addToList(ps);
        k->clearCommands();
        c.setTarget1(ps);
        pa->insertCommand(c);
    }else{
        std::cerr << "Illegal command" << std::endl;
    }

}

void Controller::stop_handler(const std::string &input) {
    // Extract the agent name from the input.
    // Retrieve the corresponding agent from the simulation model.
    // If the agent is not found, print an error message and return.
    // Otherwise, clear the agent's command list and update its state to "stopped".
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    pa->clearCommands();
    pa->setState("stopped");
}

void Controller::attack_handler(const std::string & input) {
    // Extract the thug agent name and the target peasant's name from the input.
    // Retrieve the corresponding thug agent and peasant agent from the simulation model.
    // If either agent is not found, print an error message and return.
    // Otherwise, create a new task with the peasant as the attack target and insert it as the thug's new command.
    // Clear the thug's command list.
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    if(pa->className() != "Thug"){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    std::string p_name;

    if(iss >> p_name){
        std::shared_ptr<Agent> pa1 = Model::getOBJ().getAgent(p_name);
        if(!pa1){
            std::cout << "Wrong Peasant name or command" << std::endl;
            return;
        }
        Task c(command_name);
        c.setAttack(pa1);
        pa->clearCommands();
        pa->insertCommand(c);
    }else{
        std::cerr << "Illegal command" << std::endl;
    }

}

void Controller::start_working_handler(const std::string & input) {
    // Extract the peasant agent name, farm name, and castle name from the input.
    // Retrieve the corresponding peasant agent, farm structure, and castle structure from the simulation model.
    // If any of them are not found or the peasant is not a peasant, print an error message and return.
    // Otherwise, create a new task with the farm and castle as targets and insert it as the peasant's new command.
    // Set the task status to "stopped" and clear the peasant's command list.
    std::string name, command_name;
    std::istringstream iss(input);
    iss >> name >> command_name ;

    std::shared_ptr<Agent> pa = Model::getOBJ().getAgent(name);
    if(!pa){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    if(pa->className() != "Peasant"){
        std::cout << "Wrong name or command" << std::endl;
        return;
    }

    std::string t1, t2;

    if(iss >> t1 >> t2){
        std::shared_ptr<Structure> ps1 = Model::getOBJ().getStructure(t1);
        std::shared_ptr<Structure> ps2 = Model::getOBJ().getStructure(t2);
        if(!ps1 || !ps2){
            std::cout << "Wrong site name or command" << std::endl;
            return;
        }

        if(! (ps1->className() == "Farm" && ps2->className() == "Castle")){
            std::cout << "Wrong site name or command" << std::endl;
            return;
        }

        Task c(command_name);
        c.setTarget1(ps1);
        c.setTarget2(ps2);
        c.setStatus("stopped");
        pa->insertCommand(c);
    }else{
        std::cerr << "Illegal command" << std::endl;
    }

}

void Controller::size_handler(const std::string &input) {
    // Extract the new view size from the input.
    // If the size is within the valid range (7 to 30), update the view size.
    // Otherwise, print an error message.
    std::string command;
    std::istringstream iss(input);
    int size;
    if (iss >> command >> size) {
        if (size > 6 && size <= 30)
            view.setSize(size);
        else
            std::cerr << "size not between 7 to 30" << std::endl;
    }
    else
        std::cerr << "Illegal command" << std::endl;
}

void Controller::zoom_handler(const std::string &input) {
    // Extract the new view scale (zoom) from the input.
    // If the scale is greater than 0, update the view scale.
    // Otherwise, print an error message.
    std::string command;
    std::istringstream iss(input);
    float zoom;
    if (iss >> command >> zoom) {
        if (zoom > 0)
            view.setScale(zoom);
        else
            std::cerr << "scale need to be above 0" << std::endl;
    }
    else
        std::cerr << "Illegal command" << std::endl;
}

void Controller::pan_handler(const std::string &input) {
    // Function to handle the "pan" command for adjusting the view's origin (panning).
    std::string command;
    std::istringstream iss(input);
    float x, y;
    if (iss >> command >> x >> y) {
        view.setOrigin(Point(x,y));
    }
    else
        std::cerr << "Illegal command" << std::endl;
}



