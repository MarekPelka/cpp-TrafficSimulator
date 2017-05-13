#pragma once
#include <iostream>
#include "Position.h"
#include <map>
#include "../Enums.h"
#include <memory>
//#include "Street.h"
class Street;
class Node {
public:
    Node();
    Node(int x, int y);
    Node(Position p);
    Position getPosition();
    int getNumber();
    std::string getName();
	std::map<int, std::weak_ptr<Street>> getStreetsIn();
    Position position;
    int number;
    std::string name;
    bool getIsParking();
    void setIsParking(bool p);
	void addStreetIn(Direction d, std::weak_ptr<Street> PWStreet);
private:
    bool isParking = false;
    static int all_Nodes;
	std::map<int, std::weak_ptr<Street>> streetsIn;
};