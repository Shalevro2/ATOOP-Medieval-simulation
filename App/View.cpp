//
// Created by ofirt on 22/06/2023.
//

#include <iomanip>
#include "View.h"

View::View() : size(25), scale(2), origin(0,0){

}

// Function to show the view of the simulation grid, displaying the agents and structures in their respective positions.
void View::show(){
    int counter=size - 1;
    float temp_i, temp_j;
    std::cout << "Display size: " << size << ", Scale: " << scale << ", Origin: (" << origin.getX() << ", " << origin.getY() << ")" << std::endl;
    for (int i =size-1; i>=0; i--){
        temp_i = origin.getY()+float(i)*scale;
        if (counter%3 == 0)
            std::cout << std::setw(3) << int (temp_i) << " ";
        else
            std::cout << std::setw(6);

        for (int j = 0; j < size; j++) {
            temp_j = origin.getX()+float(j)*scale;
            std::string s = Model::getOBJ().searchInPoint(temp_j, temp_i, scale);
            if (s.empty())
                std::cout << ". ";
            else
                std::cout << s.substr(0,2) ;
        }
        std::cout << std::endl;
        counter--;
    }

    counter = 0;
    std::cout << std::setw(5);
    for (int j = 0; j < size; j++) {
        if (counter%3 == 0)
            std::cout << int (origin.getX())+j*int(scale) << std::setw(6);
        counter++;
    }
    std::cout << std::endl;

}

// Function to reset the view to its default settings, setting the display size to 25, scale to 2, and origin to (0, 0).
void View::default_handler() {
    size = 25;
    scale = 2;
    origin.setX(0);
    origin.setY(0);
}
