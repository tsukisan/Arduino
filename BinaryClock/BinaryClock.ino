#include <Time.h>                                         // This is the Time function provided by Arduino.cc all credit goes to them

int hourLEDs [] = {7, 6, 5, 4, 3};                        // Pins for Hour LEDs 7 = bit 1, 3 = bit 16
int minuteLEDs [] = {13, 12, 11, 10, 9, 8};               // Pins for Minute LEDs 13 = bit 1, 8 = bit 32
int secondLED = 2;                                        // Pin for Second indicator LED
int allLEDs[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; // All pins used by LEDs for notifing when an hour passes as well as testing on power up
int setMinute = 0;                                        // Default for getting the current time by user input over Serial 9600 baud
int setHour = 0;                                          // Same as above
int currentSecLed = 0;                                    // Varriable for current status of the secondLED 1 = on 0 = off
int previousSec = 0;                                      // Varriable for the previous second's value

void setup() {
  Serial.begin(9600);                                     // Begin serial connection for input of current time and diagnostics
  for (int x = 0; x < 16; x++) {                          // Go through each pin in the array
    pinMode(allLEDs[x], OUTPUT);                          // Set pin x to output for LED
    digitalWrite(allLEDs[x], HIGH);                       // Set pin x to light the LED for startup diagnostics
  }
  serialSetTime();                                        // Jump to function to set the current time via user input over serial
}

void loop() {
  if (minute() == 0 && second() == 0) {                   // If the hour just changed:
    for (int i = 0; i < hour(); i++) {                    // Count 1 for each Hour currently passed in the day
      for (int x = 0; x < 16; x++) {                      // Count 1 for each LED in the array
        digitalWrite(allLEDs[x], HIGH);                   // Turn the current LED on
        delay(50);                                        // Wait .05 sec
        digitalWrite(allLEDs[x],LOW);                     // Turn the current LED off
      }
    }
  }
  time_t t = now();                                       // Get current time and store it to variable t
  for (int x = 0; x < 5; x++) {                           // Count 1 for each Hour LED
    digitalWrite(hourLEDs[x], bitRead(hour(t), x));       // Turn on LED if 1 Turn off LED if 0
  }
  for (int x = 0; x < 6; x++) {                           // Count 1 for each Minute LED
    digitalWrite(minuteLEDs[x], bitRead(minute(t), x));   // Turn on LED if 1 Turn off LED if 0
  }
  if (previousSec != second()) {                          // If saved value in previousSec is not equil to the current Second:
    previousSec = second();                               // Save current Second to the previousSec variable
    if (currentSecLed == 0) {                             // If the Second LED is off:
      digitalWrite(secondLED, HIGH);                      // Turn on the LED for Second indicator
      currentSecLed = 1;                                  // Value of currentSecLed is now in the on state
    } else {                                              // If the Second LED is not off:
      digitalWrite(secondLED, LOW);                       // Turn off the LED for Second indicator
      currentSecLed = 0;                                  // Value of currentSecLed is now in the off state
    }
  }    
}

void serialSetTime() {                                    // Function to set the current time by Serial input from user
  Serial.println("Input current hour in 24h format");     // Print instruction
  while(setHour == 0) {                                   // While the variable has not been set
    while (Serial.available() > 0){                       // While there is data to be read by the user input
      setHour *= 10;                                      // Multiply current value by 10 for character spacing
      setHour += (Serial.read() - '0');                   // Add the value of the current user space to the set hour space
      delay(5);                                           // Wait .05 sec as any less of a wait and it will only capture 1 character
    }
    if (setHour < 0 || setHour > 23) {                    // If the value in not within standard hour timing:
      Serial.print("Hour ");Serial.print(setHour);Serial.println(" not recognized, please try again"); // Notify user to try again
      setHour = 0;                                        // Reset variable to continue while statement
    }
  }
  Serial.println("Input current minute");                 // Print instruction
  while(setMinute == 0) {                                 // While the variable has not been set
    while (Serial.available() > 0){                       // While there is data to be read by the user input
      setMinute *= 10;                                    // Multiply current value by 10 for character spacing
      setMinute += (Serial.read() - '0');                 // Add the value of the current user space to the set minute space
      delay(5);                                           // Wait .05 sec as any less of a wait and it will only capture 1 character
    }    
    if (setMinute < 0 || setMinute > 59) {                // If the value in not within standard hour timing:
      Serial.print("Minute ");Serial.print(setMinute);Serial.println(" not recognized, please try again"); // Notify user to try again
      setMinute = 0;                                      // Reset variable to continue while statement
    }
  }
  Serial.print("Current time set to: ");Serial.print(setHour);Serial.print(":");Serial.print(setMinute); // Print current time gathered from user input
  setTime(setHour, setMinute, 0, 0, 0, 0);                // Set the time function to current time from user
}  
