//Header file which has all the classes and thei member functions defined

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QApplication> 
#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QCoreApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayout>
#include <QPixmap>
#include <QPalette>
#include <QScrollBar>

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace Ui {
    class MainWindow;
}

/*********************************************************************************/
class input_to_file
{
	public:
		string Direction;
		string Route;
		string Route_id;
};

/*********************************************************************************/

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
     input_to_file* temp;

private slots:
    void handleButtonRed();
    void handleButtonBlue();
    void handleButtonOrange();
    void handleButtonGreenB();
    void handleButtonGreenC();
    void handleButtonGreenD();
    void handleButtonGreenE();

private:
    QPushButton *Red;
    QPushButton *Blue;
    QPushButton *Orange;
    QPushButton *GreenB;
    QPushButton *GreenC;
    QPushButton *GreenD;
    QPushButton *GreenE;

};

/*********************************************************************************/

class ClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassDialog(QWidget *parent = 0);
    input_to_file* temp1;


private slots:
     void eastdirection();
     void westdirection();
     void northdirection();
     void southdirection(); 
     void direction_dialog();    

 private:
     QLabel *direction;
     QPushButton *eastbound;
     QPushButton *westbound;
     QPushButton *northbound;
     QPushButton *southbound;

};

/*********************************************************************************/

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    input_to_file* temp2;
    void file_operations();
    const char* route;
    const char *direction;

private slots:
     void showDialog();

 private:
     QLabel 	 text;
     QWidget 	 window;
     QPalette    palette;
     QLabel      imageLabel;
     QVBoxLayout *layout;
};

/*********************************************************************************/

class ImageViewer : public QMainWindow
{
    Q_OBJECT


public:
    explicit ImageViewer(QWidget *parent = 0);
    void load_image();
    input_to_file* temp3;
    const char* route;
    const char *direction;

private slots:
    void zoomIN();
    void zoomOUT();
    void home_page();
    void cancel_page();

private:
	void zoomImage(double);
	void adjustScrollBar(QScrollBar *, double );
    QWidget *image_window;
    QPushButton *zoomin;
    QPushButton *cancel;
    QPushButton *zoomout;
    QPushButton *home;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QVBoxLayout *layout;
    double scaleFactor;
};

void file_write(const char*,const  char*);

#endif // MAINWINDOW_H
