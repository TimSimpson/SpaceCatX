#ifndef FILE_GROUND_CONTROL_HPP
#define FILE_GROUND_CONTROL_HPP

#include <iostream>
#include "CatClient.hpp"
#include "Seeker.hpp"
#include "tmi.hpp"

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


template<typename CatType, typename ClientType, typename CalcType>
bool SeekMars(CatType & cat, ClientType & client, CalcType & calc) {
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
        return true;
    }
    return false;
}

void GroundControl() {
    CatClient client("localhost", "434");
    Cat<CatClient> cat(client);

    MovementCalculatorA<decltype(cat)> calc;

    // Try to reach 520, 80
    while(!SeekMars(cat, client, calc)) {
    }
    std::cout << "Space Cat X has landed safely on Mars.\n";
    return;
}

#endif
