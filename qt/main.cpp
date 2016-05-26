//The main file --> starts by calling the main window class
//TO implement the first window of th GUI


#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    input_to_file* input = new input_to_file();
 	MainWindow mainWindow;
 	mainWindow.temp = input;
    mainWindow.setWindowTitle("MBTA LIVE: Please select a route");
    mainWindow.showMaximized();
  	mainWindow.update();
    qApp->processEvents();
    return app.exec();
}