/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses call-backs on the event and RX so there's no data handling in the main loop!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <Servo.h>
Servo servo;

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 8                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

#define ONE '1'
#define TWO '2'
#define THREE '3'
#define FOUR '4'

#define BUTTON_FORWARD '5'
#define BUTTON_BACK '6'
#define BUTTON_LEFT '7'
#define BUTTON_RIGHT '8'

// int leftEn = 7;
// int rightEn = 4;
int leftFwd = 7;
int rightFwd = 3;
// int leftRvr = 9;
// int rightRvr = 5;
int leftRvr = 6;
int rightRvr = 4;
int servoPin = 5;

int angle;

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

/**************************************************************************/
/*!
    This function is called whenever select ACI events happen
*/
/**************************************************************************/
void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or advertising timed out"));
      break;
    default:
      break;
  }
}

/**************************************************************************/
/*!
    This function is called whenever data arrives on the RX channel
*/
/**************************************************************************/

// void loop() {
//   if (Serial.available())
//   {
//     angle = Serial.parseInt(); 
//     Serial.println("Angle");
//     if (angle >= 0.05 && angle <= 180)
//       {
//         servo.write(angle);
//         Serial.println(angle);
//         delay(1000);
//       }
//   }
// }

void goStraight()
{
  // digitalWrite(rightEn, HIGH);
  // digitalWrite(leftEn, HIGH);
  digitalWrite(rightRvr, LOW);
  digitalWrite(leftRvr, LOW);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(leftFwd, HIGH);
  delay(1000);
  // goStop();
}
void goBack()
{
  // digitalWrite(rightEn, HIGH);
  // digitalWrite(leftEn, HIGH);
  digitalWrite(rightRvr, HIGH);
  digitalWrite(leftRvr, HIGH);
  digitalWrite(rightFwd, LOW);
  digitalWrite(leftFwd, LOW);
  delay(1000);
  // goStop();
}
void turnRight()
{
  // digitalWrite(rightEn, HIGH);
  // digitalWrite(leftEn, HIGH);
  digitalWrite(rightRvr, HIGH);
  digitalWrite(leftRvr, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(leftFwd, HIGH);
  delay(200);
  // goStop();
}
void turnLeft()
{
  // digitalWrite(rightEn, HIGH);
  // digitalWrite(leftEn, HIGH);
  digitalWrite(rightRvr, LOW);
  digitalWrite(leftRvr, HIGH);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(leftFwd, LOW);
  delay(200);
  // goStop();
}
void goStop(){
  // digitalWrite(rightEn, LOW);
  // digitalWrite(leftEn, LOW);
  digitalWrite(rightRvr, LOW);
  digitalWrite(leftRvr, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(leftFwd, LOW);
}

void rxCallback(uint8_t *buffer, uint8_t len){
  Serial.print(F("Received "));
  Serial.print(len);
  Serial.print(F(" bytes: "));
  
  char numbutt = 0;
  if (len >= 3) numbutt = (char)buffer[2]; //make sure there is character in the spot
    
    // while(numbutt == BUTTON_FORWARD && numbutt != BUTTON_BACK && numbutt!= BUTTON_RIGHT
    // && numbutt != BUTTON_LEFT){
    //   goStraight();
    // }
    // while(numbutt == BUTTON_BACK){
    //   goBack();
    // }
    // while(numbutt == BUTTON_RIGHT){
    //   turnRight();
    // }
    // while(numbutt == BUTTON_LEFT){
    //   turnLeft();
    // }
  switch(numbutt) {
    case BUTTON_FORWARD:
      goStraight();
      break;
    case BUTTON_BACK:
      goBack();
      break;
    case BUTTON_LEFT:
      turnLeft();
      break;
    case BUTTON_RIGHT:
      turnRight();
      break;
    case ONE:
      servo.write(1);
      break;
    case TWO:
      servo.write(60);
      break;
    case THREE:
      servo.write(120);
      break;
    case FOUR:
      servo.write(180);
      break;
  }
  goStop();
}

/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
  // pinMode(leftEn, OUTPUT);
  // pinMode(rightEn, OUTPUT);
  pinMode(leftFwd, OUTPUT);
  pinMode(rightFwd, OUTPUT);
  pinMode(leftRvr, OUTPUT);
  pinMode(rightRvr, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  // Serial.println("set Angle 0 to 180");
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Callback Echo demo"));

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
void loop()
{
  uart.pollACI();
}