#include <Time.h>

int hourLEDs [] = {7, 6, 5, 4, 3};  // least significant bit first
int minuteLEDs [] = {13, 12, 11, 10, 9, 8}; //{10, 9, 8, 7, 6, 5};  
int secondLED = 2;  
int loopLEDs[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
int setMinute = 0;
int setHour = 0;
int currentSecLed = 0;
//int currentSecDir = 1;
int previousSec = 0;

void setup() {
  for (int i = 0; i< 5; i++) {
    pinMode(hourLEDs[i], OUTPUT);
  }
  for (int i = 0; i< 6; i++) {
    pinMode(minuteLEDs[i], OUTPUT);
  }
//  for (int i = 0; i < 3; i++) {
  pinMode(secondLED, OUTPUT);
//  }
  Serial.begin(9600);
  for (int j = 0; j < 16; j++) {
    digitalWrite(loopLEDs[j], HIGH);
  }
  serialSetTime();
}

void loop() {
  if (minute() == 0 && second() == 0) {
    spin(hour());
  }
  updateDisplay();
  delay(1);
}

void updateDisplay() {
  time_t t = now();
//  Serial.print(hour(t));Serial.print(":");Serial.print(minute(t));Serial.print(".");Serial.println(second(t));
  setOutput(hourLEDs, 5, hour(t));
  setOutput(minuteLEDs, 6, minute(t));
//  setOutput(secondLEDs, 6, second(t));
  updateSeconds();
}

void setOutput(int *ledArray, int numLEDs, int value) {
  for (int i= 0; i < numLEDs; i++) {
    digitalWrite(ledArray[i], bitRead(value, i));
  }
}

void updateSeconds() {
  if (previousSec != second()) {
    previousSec = second();
    if (currentSecLed == 0) {
      currentSecLed = 1;
      digitalWrite(secondLED, LOW);
    } else {
      currentSecLed = 0;
      digitalWrite(secondLED, HIGH);
    }
  }    
//    previousSec = second();
//    digitalWrite(secondLEDs[currentSecLed], LOW);
//    currentSecLed += currentSecDir;
//    if (currentSecLed > 2) {
//      currentSecLed = 1;
//      currentSecDir = -1;
//    } else if (currentSecLed < 0) {
//      currentSecLed = 1;
//      currentSecDir = 1;
//    }
//    digitalWrite(secondLEDs[currentSecLed], HIGH);
//  }
}  

void spin(int count) {
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 16; j++) {
      digitalWrite(loopLEDs[j], HIGH);
      delay(50);
      digitalWrite(loopLEDs[j],LOW);
    }
  }
}

void serialSetTime() {
  Serial.println("Input current hour in 24h format");
  while(setHour == 0) {
    while (Serial.available() > 0){
      setHour *= 10;
      setHour += (Serial.read() - '0');
      delay(5); 
    }
    if (setHour < 0 || setHour > 23) {
      Serial.print("Hour ");Serial.print(setHour);Serial.println(" not recognized, please try again");
      setHour = 0;
    }
  }
  Serial.println("Input current minute");
  while(setMinute == 0) {
    while (Serial.available() > 0){
      setMinute *= 10;
      setMinute += (Serial.read() - '0');
      delay(5); 
    }    
    if (setMinute < 0 || setMinute > 59) {
      Serial.print("Minute ");Serial.print(setMinute);Serial.println(" not recognized, please try again");
      setMinute = 0;
    }
  }
  Serial.print("Current time set to: ");Serial.print(setHour);Serial.print(":");Serial.print(setMinute);
  setTime(setHour, setMinute, 0, 0, 0, 0);
}  
