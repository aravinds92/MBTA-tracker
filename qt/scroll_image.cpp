//Class to implement scroll area for the map image

#include "mainwindow.h"

ImageViewer::ImageViewer(QWidget *parent): QMainWindow(parent) 
{

    image_window = new QWidget();
    imageLabel = new QLabel(image_window);
    scrollArea = new QScrollArea(image_window);
    scaleFactor = 1;  

    //creating push button for zoom in 
    zoomin = new QPushButton("+", image_window);
    zoomin->setGeometry(QRect(QPoint(10, 10),QSize(20, 20)));
    zoomin->move(10,10);
    connect(zoomin, SIGNAL (released()), this, SLOT (zoomIN()));

    //creating push button for zoom out 
    zoomout = new QPushButton("-", image_window);
    zoomout->setGeometry(QRect(QPoint(10, 30),QSize(20, 20)));
    zoomout->move(10,30);
    connect(zoomout, SIGNAL (released()), this, SLOT (zoomOUT()));

    //creating push button for refresh 
    home = new QPushButton("Refresh", image_window);
    home->setGeometry(QRect(QPoint(400, 10),QSize(60, 60)));
    home->move(400,10);
    connect(home, SIGNAL (released()), this, SLOT (home_page()));

    //creating a grid layout for all the above push buttons
    layout = new QVBoxLayout(image_window);
    image_window->setAutoFillBackground(true);

    //loading the image recieved from the Rasberry pi
    QPixmap load_image1("/home/root/map.png");
    imageLabel->setPixmap(load_image1);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    layout->addWidget(imageLabel);

    //setting up the scroll-area for the above image
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(true);
    layout->addWidget(scrollArea);

    //resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
};

void ImageViewer::load_image()
{
    image_window->showFullScreen();
}

void ImageViewer::zoomIN()
{
    zoomImage(1.25);
}

void ImageViewer::zoomOUT()
{
    zoomImage(0.8);
}

void ImageViewer::zoomImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    image_window->showFullScreen();
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::home_page()
{

    route = new char[temp3->Route_id.length() + 1];
    direction = new char[temp3->Direction.length() + 1];
    route = temp3->Route_id.c_str();
    direction = temp3->Direction.c_str();
    file_write(route,direction);
    ImageViewer *image_scroll = new ImageViewer();
    image_scroll->temp3 = temp3;
    delete this;
    image_scroll->load_image();
}
