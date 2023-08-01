#ifndef FLOOR_H
#define FLOOR_H

#include <QMainWindow>
#include <QtCore>
#include "ECS.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Floor; }
QT_END_NAMESPACE

class Floor: public QMainWindow
{
     Q_OBJECT

public:
    Floor(QWidget *parent = nullptr);
    ~Floor();
    ECS *ecs; // Control system
    int getFloorNum() const; // returns the floor number
    void setFloorNum(int fn); // sets the floor number

private:
    Ui::Floor *ui; // Floor User interface
    int floorNum; // Floor number

private slots:
    void pushUpButton(); // simulates the floor requesting to go up
    void pushDownButton(); // simulates the floor requesting to go down
};

#endif // FLOOR_H
