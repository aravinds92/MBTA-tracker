# MBTA-tracker
Track the current positions of trains on all MBTA lines using a Gumstix Verdex, Raspberry Pi and a LCD to display the map<br /><br />
Raspberry Pi:<br />
  Untar the directory code.tar and put it in a Raspberry pi.<br />
  Connect the raspberry pi to the internet
  Run ./script to start the application on the Raspi.<br />

KM:<br />
  Untar the directory km run the command ‘make’<br />
  Copy mbta.ko and the file in.sh to the gumstix<br />
  Run the script in.sh<br />
  To remove the kernel module, run the script ‘out.sh’<br />


QT:<br />
  Untar the directory qt.tar.<br />
  Run ‘qmake’<br />
  Run ‘qmake touchscreen.pro’<br />
  Change make file as follows:<br />
  INCPATH = -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++ \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/arm-angstrom-linux-gnueabi \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/backward \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/bits \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/debug \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include/c++/ext \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtCore \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtGui \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include/QtNetwork \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/include \
                -I/ad/eng/courses/ec/ec535/gumstix/oe/qt/mkspecs/qws/linux-arm-g++ -I. -I. -I. -I.
  
  Copy the file ‘touchsreen’ to the gumstix<br />
  Run ‘./touchscreen -qws’ to start the QT application<br />
Hardware:<br />
  Connect the pin 28 of the Gumstix to the Pin 23 on the Raspi<br />
  Connect the pin 101 of the Gumstix to the pin 24 on the Raspi<br />
  Connect the two via ethernet<br />

Software packages:<br />
	Make sure that the Gumstix is running openssh version 4 or above. Also make sure that it has the package open_scp version 4.0 or above. These are vital for the system to function.<br />

