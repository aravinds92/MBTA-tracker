//Class for Loading T data screen --> Called when T locations are fetched from the MBTA API

#include "mainwindow.h"


 LoadingDialog::LoadingDialog(QWidget *parent): QDialog(parent)	
{
	window.setFixedSize(600,600);

	layout = new QVBoxLayout(&window);

	//setting up the palette for colours
	palette = window.palette();
	palette.setColor(QPalette::Window, Qt::blue);
	window.setPalette(palette);
	window.setAutoFillBackground(true);

	//adding the text label to the window widget
	text.setText(" Fetching Current T Locations... ");
	text.setAlignment(Qt::AlignCenter);
	text.setIndent(Qt::AlignTop);
	text.setStyleSheet("QLabel {color:white;}");
	layout->addWidget(&text);

};

void LoadingDialog::showDialog()
{
	window.showFullScreen();
	file_operations();
}

//This function sets the data for sending the User Request to the Rasberry Pi
void LoadingDialog::file_operations()
{
	//Writing the inputed option to a find to send to the rasberry pi
	route = new char[temp2->Route_id.length() + 1];
	direction = new char[temp2->Direction.length() + 1];
	route = temp2->Route_id.c_str();
	direction = temp2->Direction.c_str();

	file_write(route, direction);

	ImageViewer *image_scroll = new ImageViewer();
	image_scroll->temp3 = temp2;
	image_scroll->load_image();
}


//Writes the data from the above function to a file, which is send to Rasberry Pi
//This file basically contains the user request
void file_write(const char * route,const char *direction)
{

	int Kern_File,pFile;
	char ack[3];
 	pFile = open(".input",O_RDWR);
 	system("echo "" > .input");
	write(pFile,route,strlen(route));
	write(pFile,"\n",1);
	write(pFile,direction,strlen(direction));
	close(pFile);

	//Talking to the kernel module file
	Kern_File=open("/dev/mbta", O_RDWR);
	//Sending the
	printf("Sending int\n");
	system("scp .input pi@169.254.0.2:/home/pi/codes/");
	write(Kern_File,"interrupt",10);
	

	
	//printf("ack is %s",ack);
	
	while(1)
	{
		read(Kern_File, ack, 10);
		if(strcmp(ack,"1") == 0)
		{
			cout<<"Image getting"<<endl;
			system("scp pi@169.254.0.2:/home/pi/codes/map.png /home/root/");
			cout<<"Image Received"<<endl;
			break;
		}

		else
		{
			strcpy(ack,"");
		}
		qApp->processEvents();
	}
 	
	close(Kern_File);
}

