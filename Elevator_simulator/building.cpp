#include "building.h"

Building::Building(int floor, int elevator)
    : numOfElevators(elevator)
    , numFloors(floor)
    , elevators(new Elevator[numOfElevators])
    , floors(new Floor[numFloors])
    , ecs(new ECS())
{
    //ecs->elevators = new Elevator[numOfElevators];

    ecs->elevators = new Elevator[numOfElevators];
    for(int i = 0; i < numFloors; ++i){
        floors[i].ecs = ecs;
        floors[i].setFloorNum(i+1);
    }
    for(int i = 0; i < numOfElevators; ++i){
        elevators[i].setCarNum(i+1);
        elevators[i].setNumFloors(floor);
    }
    ecs->numOfElevators = numOfElevators;
    ecs->elevators = elevators;
}

Building :: ~Building()
{
    delete[] elevators;
    delete[] floors;
    delete ecs;
}

