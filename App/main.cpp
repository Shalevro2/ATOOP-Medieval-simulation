#include <iostream>
#include "Controller.h"

int main(int argc, char* argv[]) {
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(2);
    Controller c;
    c.run(argc, argv);
    Model::getOBJ().getTime();
    return 0;
}
