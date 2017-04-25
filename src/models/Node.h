#pragma once
#include <iostream>
#include "Position.h"

class Node {
public:
    Node();
    Node(int x, int y);
    Node(Position p);
    Position getPosition();
    int getNumber();
    std::string getName();
    Position position;
    int number;
    std::string name;
    bool getIsParking();
    void setIsParking(bool p);
private:
    bool isParking = false;
    static int all_Nodes;
};