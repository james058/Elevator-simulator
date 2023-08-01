#include "elevator.h"
#include "floor.h"
#include "building.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Scenario 3: 1 passenger at floor 3 going up to floor 5

    QApplication a(argc, argv);
    int amountoffloors = 6; //Amount of floors in building
    int amountofelevators = 2; // Amount of elevators


    Building b(amountoffloors, amountofelevators); // Bulding object, has an array of elevators, floor and 1 control system

    Elevator *e  = &b.elevators[0]; //Elevator car number 1
    Elevator *e1  = &b.elevators[1]; //Elevator car number 2

    e->setFloor(2); //elevator 1 at floor 2 at the beggining of simulation
    e1->setFloor(5); //elevator 1 at floor 5 at the beggining of simulation

    Floor *f = &b.floors[2]; //Floor 3 object
    f->show();

    //safe floor is floor 1
    return a.exec();
}
