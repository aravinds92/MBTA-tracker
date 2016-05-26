QT       += core gui

 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
 
TARGET = touchscreen
TEMPLATE = app
 
SOURCES += main.cpp \
           mainwindow.cpp \
	   dialog.cpp \
	   image.cpp \
	   scroll_image.cpp

 
HEADERS  += mainwindow.h
