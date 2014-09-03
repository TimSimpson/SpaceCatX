#include <iostream>
#include "CatClient.hpp"


int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }
        CatClient client(argv[1], argv[2]);
        std::string line;
        std::cout << "Command? ";
        while(std::getline(std::cin, line)) {
            std::cout << client.Send(line) << "\n";
            std::cout << "Command? ";
        }
    } catch (const std::exception & e) {
        std::cerr << "ERROR:" << e.what() << std::endl;
    }
    return 0;
}
