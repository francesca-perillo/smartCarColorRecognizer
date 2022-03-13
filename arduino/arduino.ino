#include "esp_camera.h"

//to send data to python
#include <WebServer.h>

//to receive data from python
#include <WiFiServer.h>
#include <WiFi.h>

//contains the declaration of camera_config_t, to set configuration of camera
#include <esp32cam.h> 

//camera model
#define CAMERA_MODEL_M5STACK_WIDE 
#include "camera_pins.h"

#define RXP2 33
#define TXP2 4

//to send data on the serial port Esp32 to Elegoo board
//#include <SoftwareSerial.h>

//declaration SSID and PASSWORD of wifi 
//const char* WIFI_SSID = "Vodafone- casa Perillo"; //francesca
//const char* WIFI_PASS = "Rompipalle240199";
const char* WIFI_SSID = "Vodafone-A68422025"; //silvio
const char* WIFI_PASS = "C6YM2RJNe6bbAbx7";


//comunication between Python and Esp32
WebServer sendServer(80);
WiFiServer receiveServer(81);

//comunication between Esp32 and Elegoo
//SoftwareSerial sendDataSerial(3,1);

//char* colorByte[1] = "r";
 
//check for resolution of screen
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600);

//method to capture general immage
void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    //Serial.println("CAPTURE FAIL");
    sendServer.send(503, "", "");
    return;
  }
/*  //Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));
 */
  sendServer.setContentLength(frame->size());
  sendServer.send(200, "image/jpeg");
  WiFiClient client = sendServer.client();
  frame->writeTo(client);
}

//method to capture image with low resolution
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {
    //Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}

//method to capture image with high resolution
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    //Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}

//methot to capture image with medium resolution
void handleJpgMid()
{
  if (!esp32cam::Camera.changeResolution(midRes)) {
    //Serial.println("SET-MID-RES FAIL");
  }
  serveJpg();
}
 
void  setup(){
  WiFi.reconnect();
  Serial.begin(9600);
  Serial.setTimeout(1);
  Serial2.begin(9600, SERIAL_8N1, RXP2, TXP2);
  Serial2.setTimeout(1);
  //sendDataSerial.begin(9600);
  //Serial.println();
  
  //check if configuration is ok
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }

 // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    //Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  //to not store wifi credentials 
  WiFi.persistent(false);
  
  //WiFi.mode(WIFI_STA);
  //Serial.print("Try to establish connection with wifi ...");
   
  // Connect to access point
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  // Print our IP address
  Serial.println("SUCCESS!");//Serial.println();
  Serial.println("to send immage we use those links:");
  Serial.println("CAMERA LOW QUALITY");
  Serial.print("http://");Serial.print(WiFi.localIP());Serial.println("/cam-lo.jpg");
  //Serial.println();//Serial.println("CAMERA HIGH QUALITY");
  //Serial.print("http://");//Serial.print(WiFi.localIP());//Serial.println("/cam-hi.jpg");
  //Serial.println();//Serial.println("CAMERA MEDIUM QUALITY");
  //Serial.print("http://");//Serial.print(WiFi.localIP());//Serial.println("/cam-mid.jpg");
  //Serial.println(); //Serial.println();
  //Serial.println("to receive data from process image we use this link:");
  //Serial.println(WiFi.localIP());

  sendServer.on("/cam-lo.jpg", handleJpgLo);
  sendServer.on("/cam-hi.jpg", handleJpgHi);
  sendServer.on("/cam-mid.jpg", handleJpgMid);
  
  sendServer.begin();
  receiveServer.begin();
}

void loop() {
  //to send data to python
  sendServer.handleClient();

  //sendDataSerial.write(sendDataRed);
  
  //to receive data from python
  WiFiClient client = receiveServer.available();

  if (client) {
    while (client.connected()) {
      //Serial.println("Client connected!");
      while (client.available()>0) {
        //Serial.print("CLIENT SEND SOMETHING: ");
        char color = client.read();
        //client.write(color);
        Serial2.println(color);
        //sendDataSerial.write(sendDataRed);
        delay(1500);
      }
      delay(10);
    }
    client.stop();
    //Serial.println("Client disconnected");
  }
}
