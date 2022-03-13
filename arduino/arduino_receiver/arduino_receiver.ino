// ARDUINO UNO RECEIVER 
//COM 3

#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.h"

int color = 0;
const int r_ASCII = 114;
const int b_ASCII = 98;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Application_FunctionSet.ApplicationFunctionSet_Init();
}
void loop() { // run over and over
  delay(10);
  while(Serial.available()<=0) {
    Application_FunctionSet.ApplicationFunctionSet_Tracking();
    Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  }
  
  while(Serial.available()>0) {
    color = Serial.read();
    Serial.print("Colore:");
    Serial.println(color);
    Serial.flush();
    if (color == r_ASCII) {
      Application_FunctionSet.car_stop();
    }

    if (color == b_ASCII) {
      Application_FunctionSet.car_round();
    }
  }
}
