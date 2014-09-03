#ifndef FILE_GROUND_CONTROL_HPP
#define FILE_GROUND_CONTROL_HPP

#include <iostream>
#include "CatClient.hpp"


template<typename ClientType>
class Cat {
public:
    Cat(ClientType & client)
    :   client(client) {
        Refresh();
    }

    void AssertNotCrashed() {
        if (client.Crashed()) {
            throw std::exception("Crashed!");
        }
    }

    void MoveX(int v) {
        const auto dest = client.Y() + v;
        client.MoveX(v);
        do {
            Refresh();
            AssertNotCrashed();
        } while(client.X() < dest + 2 && client.X() > dest - 2);
    }

    void MoveY(int v) {
        const auto dest = client.Y() + v;
        client.MoveY(v);
        do {
            Refresh();
            AssertNotCrashed();
        } while(client.Y() < dest + 2 && client.Y() > dest - 2);
    }

    void Refresh() {
        X = client.X();
        Y = client.Y();
    }

    int X;
    int Y;

private:
    ClientType & client;
};


struct MovementData {
    int X, Y;
};


template<typename CatType>
struct MovementCalculator {

    MovementData operator()(CatType & cat) {
        MovementData result = {0,0};  // owl face, holding telephone
        if (cat.X < 480) {
            result.X = 100;
        } else if (cat.X > 560) {
            result.X = -100;
        }
        if (cat.Y > 120) {
            result.Y = -5;
        } else if (cat.Y < 40) {
            result.Y = 5;
        }
        return result;
    }
};


void GroundControl() {
    CatClient client("localhost", "434");
    Cat<CatClient> cat(client);

    MovementCalculator<decltype(cat)> calc;

    // Try to reach 520, 80
    while(true) {
        cat.Refresh();
        const auto movement = calc(cat);
        if (movement.X != 0) {
            cat.MoveX(movement.X);
        }
        if (movement.Y != 0) {
            cat.MoveY(movement.Y);
        }

        cat.AssertNotCrashed();
        if (client.Status() == "Mars") {
            std::cout << "Space Cat X has landed on Mars.\n";
            return;
        }
    }
}

#endif
