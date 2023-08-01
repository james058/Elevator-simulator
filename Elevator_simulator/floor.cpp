#include "floor.h"
#include "ui_floor.h"
#include <QtCore>
#include <iostream>
#include <string>

Floor::Floor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Floor)
{
    ui->setupUi(this);
    connect(ui->upButton, SIGNAL(released()), this, SLOT(pushUpButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(pushDownButton()));
    floorNum = 1;

;}

Floor::~Floor()
{
    delete ui;
}

void Floor:: pushUpButton(){
    ecs->floorRequest(floorNum, 'U');
}

void Floor:: pushDownButton(){
    ecs->floorRequest(floorNum, 'D');
}

void Floor::setFloorNum(int fn){
    floorNum = fn;
}
