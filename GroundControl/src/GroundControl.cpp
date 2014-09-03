#include <iostream>
#include "CatClient.hpp"
#include "GroundControl.hpp"


int main(int argc, char* argv[]) {
    std::cout << "GROUND CONTROL SYSTEM\n";
    try {
        GroundControl();
        return 0;
    } catch(std::exception & e) {
        std::cout << "ERROR: " << e.what() << "\n";
        return 1;
    }
}
