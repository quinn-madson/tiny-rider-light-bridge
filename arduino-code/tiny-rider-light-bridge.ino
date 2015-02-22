#include "UnoJoy.h"

const int redLane = 2;
const int yellowLane = 3;
const int greenLane = 4;
const int blueLane = 5;
const int killSwitch = 6;
const int lilRelay = 7;
const int statusLed = 13;

int redBroken = 0;
int yellowBroken = 0;
int greenBroken = 0;
int blueBroken = 0;
int relayOpen = 1;
int redMemory = 0;
int yellowMemory = 0;
int greenMemory = 0;
int blueMemory = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(redLane, INPUT);
  pinMode(yellowLane, INPUT);
  pinMode(greenLane, INPUT);
  pinMode(blueLane, INPUT);
  pinMode(killSwitch, INPUT);
  pinMode(lilRelay, OUTPUT);
  pinMode(statusLed, OUTPUT); 

  digitalWrite(killSwitch, HIGH);
  digitalWrite(lilRelay, LOW);

  blink();
  blink();
  blink();
  blink();
  
  setupUnoJoy();
  
}

void loop() {
  //delay(20);
  beamEvents();
  killEvent();
  //joystickTest();
}

void toggleRelay() {
  dataForController_t controllerData = getBlankDataForController();
  controllerData.startOn = 1;
  setControllerData(controllerData);
  
  if (relayOpen == 1) {
    relayOpen = 0;
    digitalWrite(lilRelay, HIGH);
  } else {
    relayOpen = 1;
   digitalWrite(lilRelay, LOW); 
  }
  delay(250);
}  

void killEvent() {
  int killStatus = digitalRead(killSwitch);
  //Serial.println(killStatus);
  if (killStatus == 0) {
    toggleRelay(); 
  }
}

void joystickTest() {
   
   dataForController_t controllerData = getBlankDataForController();
   controllerData.triangleOn = 1;
   controllerData.circleOn = 1;
   controllerData.squareOn = 1;
   controllerData.crossOn = 1;
   setControllerData(controllerData);
   delay(500);
  
   dataForController_t controllerData1 = getBlankDataForController();
   controllerData1.triangleOn = 1;
   setControllerData(controllerData1);
   delay(500);
   
   dataForController_t controllerData2 = getBlankDataForController();
   controllerData2.circleOn = 1;
   setControllerData(controllerData2);
   delay(500);
   
   dataForController_t controllerData3 = getBlankDataForController();
   controllerData3.squareOn = 1;
   setControllerData(controllerData3);
   delay(500);
   
   dataForController_t controllerData4 = getBlankDataForController();
   controllerData4.crossOn = 1;
   setControllerData(controllerData4);
   delay(500);
}

void blink() {
  digitalWrite(statusLed, HIGH);
  delay(500);
  digitalWrite(statusLed, LOW);
  delay(500);
}

void beamEvents() {
  redBroken = digitalRead(redLane); 
  yellowBroken = digitalRead(yellowLane); 
  greenBroken = digitalRead(greenLane); 
  blueBroken = digitalRead(blueLane); 

  dataForController_t controllerData = getBlankDataForController();

  if(redBroken == 1 /*&& redMemory == 0*/) {
    //Serial.println("red: Broken");
    digitalWrite(statusLed, HIGH);
    controllerData.triangleOn = 1;
  } 
  else if (yellowBroken == 1 /*&& yellowMemory == 0*/) { 
    //Serial.println("yellow: Broken");
    digitalWrite(statusLed, HIGH);
    controllerData.circleOn = 1;
  } 
  else if(greenBroken == 1 /* && greenMemory == 0 */) { 
    //Serial.println("green: Broken");
    digitalWrite(statusLed, HIGH);
    controllerData.squareOn = 1;
  } 
  else if(blueBroken == 1 /*&& blueMemory == 0*/) { 
    //Serial.println("blue: Broken");
    digitalWrite(statusLed, HIGH);
    controllerData.crossOn = 1;
  } 
  else {
    digitalWrite(statusLed, LOW); 
  }

  redMemory = redBroken;
  yellowMemory = yellowBroken;
  greenMemory = greenBroken;
  blueMemory = blueBroken;

  setControllerData(controllerData);

}






