//
// Created by ofirt on 19/06/2023.
//

#ifndef EX3_CONTROLLER_H
#define EX3_CONTROLLER_H

#include <iostream>
#include "Model.h"
#include "View.h"

class Controller {
private:
    static bool castles_file_handler(char *argv);
    static bool farms_file_handler(char *argv);
    static void create_handler(const std::string& input);
    static void default_handler(const std::string&);
    static void course_handler(const std::string&);
    static void position_handler(const std::string&);
    static void destination_handler(const std::string&);
    static void stop_handler(const std::string&);
    static void attack_handler(const std::string&);
    static void start_working_handler(const std::string&);
    void size_handler(const std::string&);
    void zoom_handler(const std::string&);
    void pan_handler(const std::string&);

    View view;

public:

    void run(int argc, char* argv[]);
    bool do_move();
    void do_go();
    void do_show();

};


#endif //EX3_CONTROLLER_H
