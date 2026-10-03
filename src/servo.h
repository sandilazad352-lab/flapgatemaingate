#ifndef SERVO_H
#define SERVO_H
#include <Arduino.h>
#include <ESP32Servo.h>

// Pin definitions for the servos
extern int servoPin1;
extern int servoPin2;

// Positions for the servos
extern int servoStartPos;
extern int servoEndPos;

// Declare the Servo objects
extern Servo servo1;
extern Servo servo2;

// Function declarations
void servoInit();
void servoRun();
void doorOpen();
void doorClose();

#endif // SERVO_H
