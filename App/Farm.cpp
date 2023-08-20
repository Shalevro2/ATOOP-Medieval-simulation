//
// Created by ofirt on 19/06/2023.
//

#include "Farm.h"

#include <utility>

Farm::Farm(std::string n, float x, float y, int a, int r): Structure(std::move(n),x,y,a), rate(r) {

}

void Farm::update() {
    setAmount(rate);
}
