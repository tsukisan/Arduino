#include "Notes.h"                                                        
#include "Wire.h"
#include "WiiClassic.h"

WiiClassic wiiClassy = WiiClassic();

const int speakerPin = 12;                                                // Define the pin used for the speaker
                                                                          // Format for array: {number of notes, note to play, durration, note to play, durration, ...
const int theme[] = {11,                                                  // Array for Theme song
  NOTE_E4, 8, NOTE_E4, 8, NOTE_H, 8, NOTE_E4, 8, NOTE_H, 8, NOTE_C4, 8, NOTE_E4, 8, NOTE_H, 8, NOTE_G4, 8, NOTE_H, 3, NOTE_G3, 8};
const int life[] = {6,                                                    // Array for 1-up sound effect
  NOTE_E5, 10, NOTE_G5, 10, NOTE_E6, 10, NOTE_C6, 10, NOTE_D6, 10, NOTE_G6, 10};
const int flagpole[] = {27,                                               // Array for Flag pole sound effect & song
  NOTE_G2, 10, NOTE_C3, 10, NOTE_E3, 10, NOTE_G3, 10, NOTE_C4, 10, NOTE_E4, 10, NOTE_G4, 3, NOTE_E4, 3, NOTE_GS2, 10, NOTE_C3, 10, 
  NOTE_DS3, 10, NOTE_GS3, 10, NOTE_C4, 10, NOTE_DS4, 10, NOTE_GS4, 3, NOTE_DS4, 3, NOTE_AS2, 10, NOTE_D3, 10, NOTE_F3, 10, 
  NOTE_AS3, 10, NOTE_D4, 10, NOTE_F4, 10, NOTE_AS4, 3, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10, NOTE_C5, 2};
const int death[] = {17,                                                  // Array for Death sound effect & song
  NOTE_C4, 32, NOTE_CS4, 32, NOTE_D4, 16, NOTE_H, 4, NOTE_H, 2, NOTE_B3, 8, NOTE_F4, 8, NOTE_H, 8, NOTE_F4, 8, NOTE_F4, 6, 
  NOTE_E4, 6, NOTE_D4, 6, NOTE_C4, 8, NOTE_E3, 8, NOTE_H, 8, NOTE_E3, 8, NOTE_C3, 8};
const int gameover[] = {15,                                               // Array for Game over song
  NOTE_C4, 8, NOTE_H, 8, NOTE_H, 8, NOTE_G3, 8, NOTE_H, 4, NOTE_E3, 4, NOTE_A3, 6, NOTE_B3, 6, NOTE_A3, 6, NOTE_GS3, 6, NOTE_AS3, 6, 
  NOTE_GS3, 6, NOTE_G3, 8, NOTE_F3, 8, NOTE_G3, 4};

void setup() {
  Wire.begin();                                                           // Begin wire connection
  Serial.begin(9600);                                                     // Begin Serial on 9600 baud
  wiiClassy.begin();                                                      // Initialize the Wii Classic controller
  wiiClassy.update();                                                     // Gather data from the controller for the first time as this isually bogus
  Serial.println("Mario Wii Classic Soundboard initializtion complete");  // Print basic button mapping for reference
  Serial.println("---------------------------------------------------");
  Serial.println("Button Mapping:");
  Serial.println("Start: Theme song");
  Serial.println("A: 1-up sound effect");
  Serial.println("B: Flag pole sound effect & song");
  Serial.println("X: Death sound effect & song");
  Serial.println("Y: Game over song");
  Serial.println("Home: Re-display this menu");
  Serial.println("---------------------------------------------------");
}

void loop() {
  wiiClassy.update();                                                     // Poke the controller for status
  if (wiiClassy.leftShoulderPressed()) {                                  // If the Left shoulder button is fully depressed:

  } else if (wiiClassy.rightShoulderPressed()) {                          // If the Right shoulder button is fully depressed:

  } else if (wiiClassy.lzPressed()) {                                     // If the LZ button is pressed

  } else if (wiiClassy.rzPressed()) {                                     // If the RZ button is pressed

  } else if (wiiClassy.selectPressed()) {                                 // If the Select button is pressed

  } else if (wiiClassy.homePressed()) {                                   // If the Home button is pressed
    Serial.println("Button Mapping:");                                    // Print basic button mapping for reference
    Serial.println("Start: Theme song");
    Serial.println("A: 1-up sound effect");
    Serial.println("B: Flag pole sound effect & song");
    Serial.println("X: Death sound effect & song");
    Serial.println("Y: Game over song");
    Serial.println("Home: Re-display this menu");
    delay(500);                                                           // Wait .5 sec to prevent repeat of printing
    Serial.println("---------------------------------------------------");
  } else if (wiiClassy.startPressed()) {                                  // If the Start button is pressed
    Serial.println("Start button pressed");                               // Print button pressed
    Serial.println("Begin playing Theme song");                           // Print begin of melody
    for (int thisNote = 1; thisNote < (theme[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, theme[thisNote], (1000 / theme[thisNote + 1));     // Play the single note
      delay((1000 / theme[thisNote + 1) * 1.30);                          // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
    Serial.println("Theme song complete");                                // Print that the song is complete
    Serial.println("---------------------------------------------------");
  } else if (wiiClassy.aPressed()) {                                      // If the A button is pressed
    Serial.println("A button pressed");                                   // Print button pressed
    Serial.println("Begin playing 1-up sound effect");                    // Print begin of melody
    for (int thisNote = 1; thisNote < (life[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, life[thisNote], (1000/life[thisNote + 1]));        // Play the single note
      delay((1000/life[thisNote + 1]) * 1.30);                            // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
    Serial.println("1-up sound effect complete");                         // Print that the song is complete
    Serial.println("---------------------------------------------------");
  } else if (wiiClassy.bPressed()) {                                      // If the B button is pressed
    Serial.println("B button pressed");                                   // Print button pressed
    Serial.println("Begin playing Flag pole sound effect & song");        // Print begin of melody
    for (int thisNote = 1; thisNote < (flagpole[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, flagpole[thisNote], (1000/flagpole[thisNote + 1]));// Play the single note
      delay((1000/flagpole[thisNote + 1]) * 1.30);                        // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
    Serial.println("Flag pole sound effect & song complete");             // Print that the song is complete
    Serial.println("---------------------------------------------------");
  } else if (wiiClassy.xPressed()) {                                      // If the X button is pressed
    Serial.println("X button pressed");                                   // Print button pressed
    Serial.println("Begin playing Death sound effect & song");            // Print begin of melody
    for (int thisNote = 1; thisNote < (death[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, death[thisNote], (1000/death[thisNote + 1]));      // Play the single note
      delay((1000/death[thisNote + 1]) * 1.30);                           // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
    Serial.println("Death sound effect & song complete");                 // Print that the song is complete
    Serial.println("---------------------------------------------------");
  } else if (wiiClassy.yPressed()) {                                      // If the Y button is pressed
    Serial.println("Y button pressed");                                   // Print button pressed
    Serial.println("Begin playing Game over song");                       // Print begin of melody
    for (int thisNote = 1; thisNote < (gameover[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, gameover[thisNote], (1000/gameover[thisNote + 1]));// Play the single note
      delay((1000/gameover[thisNote + 1]) * 1.30);                        // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
    Serial.println("Game over song complete");                            // Print that the song is complete
    Serial.println("---------------------------------------------------");
  }
  delay(1);                                                               // Delay .01 sec to not overload the controller
}
