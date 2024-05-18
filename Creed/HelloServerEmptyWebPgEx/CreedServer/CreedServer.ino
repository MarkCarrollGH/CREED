//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Two-Way communication ESP32 to Control LED
//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <WebServer.h>
#include "homepage.h"

#define BUTTON 21
#define LED 15
#define SERVO 27

WebServer website(80);

const char* ssid = "Weeboo";
const char* password = "gyatdamn";
Servo servoMotor;

int currentState;

uint8_t broadcastAddress[] = {0x10, 0x97, 0xBD, 0x8E, 0x42, 0x70};

int turnOnCam = 0;

String success; //--> Variable to store if sending data was successful

String response;
//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int resp;
    String str;
} struct_message_send;

struct_message send_Data; // Create a struct_message to send data.

struct_message receive_Data;
//----------------------------------------

esp_now_peer_info_t peerInfo;

String result(){
  return response;
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  response = receive_Data.str;
  Serial.print("Receive Data: ");
  Serial.println(response);
  Serial.println("<<<<<");
  website.handleClient();
}

void handleRoot() {
  String message = homePagePart1 + result() + homePagePart2;
  website.send(200, "text/html", message);
}

void setup() {
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servoMotor.setPeriodHertz(50);    
  servoMotor.attach(SERVO, 500, 2400);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);

  esp_now_register_recv_cb(OnDataRecv); 

  /*
  website.on("/", handleRoot);
  website.on("/inline", []() {
    website.send(200, "text/html", "this works as well");
  }); 

  website.begin();
  Serial.println("HTTP server started");
  */
}

void loop() {
  
  currentState = digitalRead(BUTTON);

  if(currentState == HIGH) {
    Serial.println("");
    Serial.println("Button pressed");
    digitalWrite(LED,HIGH);
    turnOnCam = !turnOnCam;
    send_Data.resp = turnOnCam;
    Serial.println();
    Serial.print(">>>>> ");
    Serial.println("Send data");
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
    delay(2000);
    for (int pos = 100; pos >= 0; pos -= 1) {
      servoMotor.write(pos);
      delay(15);
    }
    delay(800);
    for (int pos = 0; pos <= 100; pos += 1) {
      servoMotor.write(pos);
      delay(15);
    }
    digitalWrite(LED,LOW);
  }
}