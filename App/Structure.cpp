//
// Created by ofirt on 11/06/2023.
//

#include "Structure.h"

#include <utility>
#include <stdexcept>
#include <iostream>

Structure::Structure(std::string n , float x, float y, int a): SimObject(std::move(n),x,y), amount(a) {

}

int Structure::getAmount() const {
    return amount;
}

void Structure::setAmount(int aa) {
    /// the function add or decrease the amount by the argument aa
    /// to add enter positive number, to  decrease enter negative number
    amount += aa;
}

void Structure::printStatus() {
    std::cout << className() << " " << getName() << " at position (" << getLocation().getX() << ", "
              << getLocation().getY() << "), " << "Inventory: " << getAmount() << std::endl;
}

void Structure::makeEmpty() {
    amount = 0;
}
