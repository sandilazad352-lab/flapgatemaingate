#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

// Define button pins
#define GREEN_PIN   25
#define YELLOW_PIN  32
#define RED_PIN     33



// Function declarations
void setupLED();
void onGreen(int);
void onYellow(int);
void onRed(int);




#endif // BUTTON_INTERRUPT_H
