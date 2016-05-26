//Main Window class - imolements the first page of the GUI

#include "mainwindow.h"

 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Creating the route buttons
    Red = new QPushButton("RED", this);
    Red->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    Red->move(20,10);
    connect(Red, SIGNAL (released()), this, SLOT (handleButtonRed()));

    Blue = new QPushButton("BLUE", this);
    Blue->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    Blue->move(250,10);
    connect(Blue, SIGNAL (released()), this, SLOT (handleButtonBlue()));

    Orange = new QPushButton("ORANGE", this);
    Orange->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    Orange->move(20,70);
    connect(Orange, SIGNAL (released()), this, SLOT (handleButtonOrange()));

    GreenB = new QPushButton("GREEN-B", this);
    GreenB->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    GreenB->move(250,70);
    connect(GreenB, SIGNAL (released()), this, SLOT (handleButtonGreenB()));

    GreenC = new QPushButton("GREEN-C", this);
    GreenC->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    GreenC->move(20,130);
    connect(GreenC, SIGNAL (released()), this, SLOT (handleButtonGreenC()));

    GreenD = new QPushButton("GREEN-D", this);
    GreenD->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    GreenD->move(250,130);
    connect(GreenD, SIGNAL (released()), this, SLOT (handleButtonGreenD()));

    GreenE = new QPushButton("GREEN-E", this);
    GreenE->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    GreenE->move(135,190);
    connect(GreenE, SIGNAL (released()), this, SLOT (handleButtonGreenE()));
 
    
}
 
//Route buttons handler --> Called when buttons clicked 
void MainWindow::handleButtonRed()
{
    temp->Route = "Red";
    temp->Route_id = "0";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(Red,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));
}

void MainWindow::handleButtonBlue()
{
    temp->Route = "Blue";
    temp->Route_id = "2";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(Blue,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));
}

void MainWindow::handleButtonOrange()
{
    temp->Route = "Orange";
    temp->Route_id = "1";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(Orange,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));
}

void MainWindow::handleButtonGreenB()
{ 
    temp->Route = "Green";
    temp->Route_id = "3";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(GreenB,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));
}

void MainWindow::handleButtonGreenC()
{
    temp->Route = "Green";
    temp->Route_id = "4";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(GreenC,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));

}

void MainWindow::handleButtonGreenD()
{
    temp->Route = "Green";
    temp->Route_id = "5";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(GreenD,SIGNAL(clicked()), dialog, SLOT(direction_dialog()));
}

void MainWindow::handleButtonGreenE()
{
    temp->Route = "Green";
    temp->Route_id = "6";
    ClassDialog *dialog = new ClassDialog(this);
    dialog->temp1 = temp ; 
    connect(GreenE,SIGNAL(clicked()), dialog, SLOT(direction_dialog())); 
}



