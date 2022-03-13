# Smart Car Color Recognition
## Introduction
This project uses "Smart Robot Car V4.0 with camera" (link: https://www.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0).
To be precise, the car reacts to the colors (red and blue at the moment), thansk to the python's OpenCV library. 
## Project structure
<img src="https://img.icons8.com/color/20/000000/folder-invoices--v1.png"/> Arduino

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> app_httpd.cpp

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> arduino.ino

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> camera_index.h

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> camera_pins.h
 
&emsp;&emsp;<img src="https://img.icons8.com/color/20/000000/folder-invoices--v1.png"/> arduino_receiver

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> ApplicationFunctionSet_xxx0.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> ApplicationFunctionSet_xxx0.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> ArduinoHson-v6.11.1.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> DeviceDriverSet_xxx0.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> DeviceDriverSet_xxx0.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> I2Cdev.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> I2Cdev.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MPU6050.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MPU6050.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MPU6050_getdata.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MPU6050_getdata.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MsTimer2.cpp

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> MsTimer2.h

&emsp;&emsp;&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> arduino_reciver.ino

## Arduino code
Arduino code is composed by two parts. In order to recognize the color, it has been used python code
### Send Image
