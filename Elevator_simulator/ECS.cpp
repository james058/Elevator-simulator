#include "ECS.h"

ECS::ECS(){

}

ECS::~ECS(){

}

void ECS::floorRequest(int floor, char direction){
    if (direction == 'U'){
        QString message = QString("received request from floor %1 going up").arg(floor);
        qInfo() << message;
        for (int i = 0; i < numOfElevators; ++i) {
            if(elevators[i].getDirection().compare("Idle") == 0 || elevators[i].getDirection().compare("Up") == 0){
                QString m = QString("Sending elevator %1").arg(i+1);
                elevators[i].setFloor(floor);
                //elevators[i].addPassengers(1);
                elevators[i].show();
                qInfo() << m;
                break;
            }
       }
    }
    else{
        QString message = QString("received request from floor %1 going down").arg(floor);
        qInfo() << message;
        for (int i = 0; i < numOfElevators; ++i) {
            if(elevators[i].getDirection().compare("Idle") == 0 || elevators[i].getDirection().compare("Up") == 0){
                QString m = QString("Sending elevator %1").arg(i+1);
                elevators[i].setFloor(floor);
                //elevators[i].addPassengers(1);
                //qInfo()<<elevators->getCarNum();
                elevators[i].show();
                qInfo() << m;
                break;

            }
       }
    }  
}


