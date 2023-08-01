#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <QMainWindow>
#include <QtCore>
#include "elevator.h"

using namespace std;
class ECS

{

public:
    ECS();
    ~ECS();
   void floorRequest(int floor, char direction); // receives a request from a floor with its floor number and direction and allocates an elevator to satsfy it
   Elevator *elevators; // array of elevators
   int numOfElevators; // number of elevators
};

#endif // ECS_H
