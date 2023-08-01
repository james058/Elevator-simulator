#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <QMainWindow>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui { class Elevator; }
QT_END_NAMESPACE


class Elevator : public QMainWindow
{

    Q_OBJECT

public:
    Elevator(QWidget *parent = nullptr); //Constructor
    ~Elevator(); // Destructor
    int getFloor() const; // get the floor elevator is currently at at
    void satisfyRequests(); // Satisfy all destination floors
    void setCarNum(int car);  // sets elevator car#
    void setFloor(int cur); // set the current floor to the given floor
    int getCarNum() const; // gets elevator car#
    void addPassengers(int p);  //simulates adding a the given number of passengers from elevator
    int getCurrentWeight() const; // get weight that elevator is currently holding
    void removePassengers(int p); //simulates removing a the given number of passengers from elevator
    void setNumFloors(int f); // set number of floors for elevator
    std::string getDirection() const; // get current state of elevator: idle, going up or going down

private:
    int weightcapacity = 500; // max weight elevator can hold, currently 500kg
    int currentweight; // current weight in the elevator
    Ui::Elevator *ui;
    int carNum; //Car#
    std::string direction = "Idle"; // direction of elevator going up, down or default value: not moving(idle)
    int currentfloor; // floor elevator is currently at
    QTimer *timer; // timer for the door
    QTimer *timer_up;  // timer to simulate elevator moving downwards
    QTimer *timer_down; // timer to simulate elevator moving upwards
    int numfloors; //number of floors in building
    QVarLengthArray<int> floorsToGo; // stores the floors that elevator has to go to
    bool overload = false; //tells elevator if it is overloaded or not
    bool fire_p = false; //tells elevator there is a fire
    bool p_out = false; // //tells elevator there is a power outage

private slots:

    void openDoor(); //opens elevator door
    void closeDoor(); // closes elevator door
    void ringBell(); // rings elevator bell
    void floorPressed(); //gets called when an elevator floor button is pressed so it adds it to the list of floors to go to
    void newFloorUp(); // Gets called when we arrive at a new floor when going up
    void newFloorDown(); // Gets called when we arrive at a new floor when going down
    void sendHelpSignal(); // handles what happens when the help button is pressed
    void overLoad(); // handles what happens when the overload button is pressed, overloads the elevator
    void fire(); // handles what happens when the fire button is pressed
    void doorObstacle(); // handles what happens when the door obstacle button is pressed
    void powerOut(); // handles what happens when the Power Out button is pressed


};
#endif // ELEVATOR_H
