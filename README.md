# Smart Car Color Recognition
## Introduction
This project uses "Smart Robot Car V4.0 with camera". At [this link](https://www.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0) it is possible to see all the componens provided by this kit. To be precise, the car follows a black line but it also reacts to the colors such as for example a red traffic sign or blue one. In particular, at the moment, when the robot car sees a red color, it'll stop for two seconds; when the robot car sees a blue color, it'll tourn around. All of these features were implemented by using the Arduino IDE, python's OpenCV and Numpy libraries.

## Explainer video
https://user-images.githubusercontent.com/57345578/158220047-0b580dc4-a6f4-4b2b-b78d-20550f9b1072.mp4

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

<img src="https://img.icons8.com/color/20/000000/folder-invoices--v1.png"/> python

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> col_det_screen_view.py

&emsp;<img src="https://img.icons8.com/plasticine/20/000000/file.png"/> color_detection.py

## Arduino code
Arduino code is composed by three parts:
1. at the beginning, in order to recognize colors it is necessary to send images by esp32 module, on python client;
2. after this, the second step is to get back the python result after the image processing;
3. so, now, the esp32 module sends the response to arduino board in order to control the wheels. 
4. wheels control

### 1. Send Image to python client
The first step is to send frame by frame images to a client implemented in python. The `WebServer.h` library is used for this. In the file 	`arduino.ino`, below the main folder, you'll find everything you're looking for to start. There are several comments in the code to help you in finding. 

### 2. Get back the python response
The second step is to get back the python response. To do this we have been used `WiFiServer.h` and `WiFi.h` libraries. Remember that, if you have started the previous WebServer on the port 80 (for example) you mustn't choose the same port for the WiFiServer. As we have just said previously,there are several comments in the code to help you in finding.

### 3. Send response to arduino board
The third step is to send response to arduino board. To do this, since that the esp32 module has three `Serial`(s) ([documentation here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)) we just used this feature to send data from esp32module to Arduino Uno board. As we have just said previously, there are several comments in the code to help you in finding.

### 4. Wheels control
This part is developed in the `arduino_receiver.ino` file, below the folder named in the same way. In particular, the code takes up the line tracking algorithm (just implemented by Elegoo team), but in addition it reads from the _Serial_ and checks the _ASCII code_ just red in order to check whether the color detected is red ('r') or blue ('b'). 

## Python code
Python code is composed by two files, that are stored in the folder `python`, below the main folder. 
- `color_detection.py` file is very useful in order to find the values of HSV colors. The values that you'll find by using this script must be insert in the second file in order to detect color. 
- `col_det_screen_view.py` file is the core of the image processing. As we preaviously said, this script takes frame by frame the images from the ip address, looking for a red or blue color. When it detects them, it draws a circle around the object and labels it with the color. In addition, through a socket it's possible to send the result of color detection to the server implemented in Arduino. As the previous codes, there are several comments in order to be absolutely clear. 

# Contact us
For more info about this project you can contact us here:
```
francescaperillo15@gmail.com
```
```
ussilvio@gmail.com
```
