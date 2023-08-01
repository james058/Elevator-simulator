#include "elevator.h"
#include "ui_elevator.h"
#include <QtCore>
#include <iostream>
#include <string>

Elevator::Elevator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Elevator)
{
    ui->setupUi(this);
    connect(ui->doorOpen, SIGNAL(released()), this, SLOT(openDoor()));
    connect(ui->doorClose, SIGNAL(released()), this, SLOT(closeDoor()));

    timer = new QTimer(this);
    timer_up = new QTimer(this);
    timer_down =  new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(closeDoor()));
    connect(timer_up, SIGNAL(timeout()), this, SLOT(newFloorUp()));
    connect(timer_down, SIGNAL(timeout()), this, SLOT(newFloorDown()));
    connect(ui->help, SIGNAL(released()), this, SLOT(sendHelpSignal()));
    connect(ui->overload, SIGNAL(released()), this, SLOT(overLoad()));
    connect(ui->fire, SIGNAL(released()), this, SLOT(fire()));
    connect(ui->obstacle, SIGNAL(released()), this, SLOT(doorObstacle()));
    connect(ui->powerout, SIGNAL(released()), this, SLOT(powerOut()));

    numfloors = 5; // Default number of floors in case it is not changed
    QPushButton *floorButtons[numfloors];
    for (int i = 0; i < numfloors; ++i) {
       QString floorb = "floor" + QString::number(i+1);
       floorButtons[i] = Elevator::findChild<QPushButton *>(floorb);
       connect(floorButtons[i], SIGNAL(released()), this, SLOT(floorPressed()));
    }
;}

Elevator::~Elevator()
{
    delete ui;
    delete timer;
    delete timer_up;
    delete timer_down;
}

void Elevator::openDoor(){
    if(fire_p == true || p_out == true){
        QString m = QString("Gently disembark elevator!");
        ui->display->setText(m);
        qInfo("Audio warning message: Safe floor reached gently disembark elevator ");
        fire_p = false;
        p_out = false;
    }
    ringBell();
    QString m = QString("Door open at floor %1").arg(currentfloor);
    qInfo()<<m;
    timer->start(10000);
}

void Elevator::closeDoor(){
    timer->stop();
    ringBell();
    QString m = QString("Door close at floor %1").arg(currentfloor);
    qInfo()<<m;
    satisfyRequests();
}

void Elevator::ringBell(){
   qInfo("Bell ring");
}

void Elevator::newFloorUp(){
   int nf = currentfloor+1;
   QString dir = QString::fromStdString(direction);
   QString m = QString("Arriving at floor %1 going " + dir).arg(nf);
   qInfo()<< m;
   int len = floorsToGo.length();
   setFloor(nf);
   for (int i = 0; i < len; ++i) {
      if(nf == floorsToGo.at(i)){
          QString floorb = "floor" + QString::number(nf);
          QPushButton *floorButton = Elevator::findChild<QPushButton *>(floorb);
          floorButton->setStyleSheet("");
          openDoor();
          timer_up->stop();
          break;
      }
   }
}

void Elevator::newFloorDown(){
   int nf = currentfloor-1;
   QString dir = QString::fromStdString(direction);
   QString m = QString("Arriving at floor %1 going " + dir).arg(nf);
   qInfo()<< m;
   int len = floorsToGo.length();
   setFloor(nf);
   for (int i = 0; i < len; ++i) {
      if(nf == floorsToGo.at(i)){
          QString floorb = "floor" + QString::number(nf);
          QPushButton *floorButton = Elevator::findChild<QPushButton *>(floorb);
          floorButton->setStyleSheet("");
          openDoor();
          timer_down->stop();
          break;
      }
   }
}

void Elevator::satisfyRequests(){
    int len = floorsToGo.length();
    //qInfo() << len;
    if(len>0 && currentfloor!= floorsToGo.last()){
        if(direction.compare("Up") == 0){
            timer_up->start(2000);
        }
        else if(direction.compare("Down") == 0){
            timer_down->start(2000);
        }
    }else{
        floorsToGo.clear();
    }
}

int Elevator::getFloor() const{
    return currentfloor;
}

void Elevator::setFloor(int cur){
    QString m = QString("Car#: %1").arg(carNum);
    ui->carNum->setText(m);
    /*For testing*/
    currentfloor = cur;
    QString c = QString::number(currentfloor);
    ui->display->setText(c);

}

void Elevator::floorPressed(){
    if(overload == true){
        QString m = QString("Reduce weight in elevator");
        ui->display->setText(m);
        qInfo("Audio warning message: Reduce elevator weight");
    }
    else{
        QPushButton *button = (QPushButton *) sender();
        QString val = button->text();
        int v = val.toInt();
        int l = floorsToGo.length();

        if(v == currentfloor){
            openDoor();
        }

        else if(l == 0){
            direction = "Up";
            if(v > currentfloor){
                direction = "Up";
                button->setStyleSheet("background-color:red");
                floorsToGo.insert(l,v);
                satisfyRequests();
            }else if(v < currentfloor){
                direction = "Down";
                button->setStyleSheet("background-color:red");
                floorsToGo.insert(l,v);
                satisfyRequests();
            }
        }
        else if(l > 0){
            if(direction.compare("Up") == 0 && v > currentfloor){
                button->setStyleSheet("background-color:red");
                floorsToGo.insert(l,v);
                satisfyRequests();
            }

            else if(direction.compare("Down") == 0 && v < currentfloor){
                button->setStyleSheet("background-color:red");
                floorsToGo.insert(l,v);
                satisfyRequests();
            }
        }
     }
}

void Elevator::setCarNum(int car){
    carNum = car;
}

int Elevator::getCarNum() const{
    return carNum;
}

void Elevator::addPassengers(int p){
    currentweight += (p*60);
    if(currentweight>=weightcapacity){
       overload = true;
       QString m = QString("Reduce weight in elevator");
       ui->display->setText(m);
       qInfo("Audio warning message: Reduce elevator weight");
    }else{
        QString m = QString("%1 passengers entered the elevator").arg(p);
        qInfo() << m;
    }
}

int Elevator::getCurrentWeight() const{
    return currentweight;
}

void Elevator::sendHelpSignal(){
    for (int var = 0; var < 3; ++var) {
       qInfo("Calling building safety...");
    }
     qInfo("Hi, what's your emergency");
}

void Elevator::removePassengers(int p){
    currentweight -= (p*60);
    QString m = QString("%1 passengers exited the elevator").arg(p);
    qInfo() << m;

    if(currentweight<weightcapacity){
       overload = false;
       QString message = QString::number(currentfloor);
       ui->display->setText(message);
    }
}

std::string Elevator::getDirection() const{
    return direction;
}
void Elevator::overLoad(){
    addPassengers(9);
}

void Elevator::fire(){
    fire_p = true;
    QString m = QString("Fire! elevator going to safe floor 1");
    ui->display->setText(m);
    qInfo("Audio warning message: gently disembark elevator when it reaches floor 1");
    direction = "Down";
    floorsToGo.insert(floorsToGo.length(),1);
    satisfyRequests();
}

void Elevator::doorObstacle(){
    for (int i = 0; i < 3; ++i) {
        qInfo("door obstructed");
    }
    QString m = QString("Remove door obstacle!");
    ui->display->setText(m);
    qInfo("Audio warning message: Remove door obstacle! ");
}

void Elevator::powerOut(){
    p_out = true;
    QString m = QString("Power outage!");
    ui->display->setText(m);
    qInfo("Audio warning message: Gently Disembark elevator at floor 1! ");
    direction = "Down";
    floorsToGo.insert(floorsToGo.length(),1);
    satisfyRequests();
}
void Elevator::setNumFloors(int f){
    numfloors = f;

}





