//This class creates a dialog box to select the direction of the route selected in the 
//previous window

#include "mainwindow.h"


 ClassDialog::ClassDialog(QWidget *parent): QDialog(parent)
{

	//defing the pushbuttons for the directions on the routes
   	eastbound = new QPushButton("EAST BOUND", this);
	eastbound->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
	eastbound->move(20,10);	
	connect(eastbound, SIGNAL (released()), this, SLOT (eastdirection()));

   	westbound = new QPushButton("WEST BOUND", this);
	westbound->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
	westbound->move(250,10);
	connect(westbound, SIGNAL (released()), this, SLOT (westdirection()));

   	northbound = new QPushButton("NORTH BOUND", this);
	northbound->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
	northbound->move(20,10);
	connect(northbound, SIGNAL (released()), this, SLOT (northdirection()));

   	southbound = new QPushButton("SOUTH BOUND", this);
   	southbound->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
   	southbound->move(250,10);
   	connect(southbound, SIGNAL (released()), this, SLOT (southdirection())); 
	
};

//handlers of the above defined buttons
void ClassDialog::eastdirection()
{
	temp1->Direction = "Eastbound";
	LoadingDialog *loading = new LoadingDialog(this);
	loading->temp2 = temp1;
    connect(eastbound, SIGNAL (clicked()), loading, SLOT(showDialog()));
}


void ClassDialog::westdirection()
{
	temp1->Direction= "Westbound";
	LoadingDialog *loading = new LoadingDialog(this);
	loading->temp2 = temp1;
    connect(westbound, SIGNAL (clicked()), loading, SLOT(showDialog()));
}

void ClassDialog::northdirection()
{
	temp1->Direction = "Northbound";
	LoadingDialog *loading = new LoadingDialog(this);
	loading->temp2 = temp1;
    connect(northbound, SIGNAL (clicked()), loading, SLOT(showDialog()));
}


void ClassDialog::southdirection()
{
	temp1->Direction= "Southbound";
	LoadingDialog *loading = new LoadingDialog(this);
	loading->temp2 = temp1;
    connect(southbound, SIGNAL (clicked()), loading, SLOT(showDialog()));
}


//this function displays the direction of the route
//Green and Blue run in east and west direction
//Red and Orange run in North and South direction  
void ClassDialog::direction_dialog()
{

 	if((temp1->Route.compare("Green") == 0) || (temp1->Route.compare("Blue") == 0))
 	{
 		delete northbound;
	 	delete southbound;	
	}

	if((temp1->Route.compare("Red") == 0) || (temp1->Route.compare("Orange") == 0))
 	{
	 	delete eastbound;
	 	delete westbound;
	}

	setWindowTitle("Please Select the Direction");
    show();
}

    
