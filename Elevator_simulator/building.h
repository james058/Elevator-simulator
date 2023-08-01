#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <iomanip>
#include <string>
#include <QMainWindow>
#include <QtCore>
#include "floor.h"
#include "elevator.h"
#include "ECS.h"

using namespace std;

class Building
{

public:
    Building(int floor = 0, int elevator = 0);
    ~Building();
    int numOfElevators; // number of elevators in building
    int numFloors; // number of floors in building
    Elevator *elevators; //elevators
    Floor *floors; // floors
    ECS *ecs; // Control system
};




#endif // BUILDING_H
