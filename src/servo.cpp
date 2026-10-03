#include "servo.h" // Include the header file for servo control
#include "light.h"

// Pin assignments (can be defined here or in the main file)
int servoPin1 = 26; // GPIO 18 for the first servo
int servoPin2 = 27; // GPIO 19 for the second servo

// Position values for the servos
int servoStartPos = 0; // Start position (0 degrees)
int servoEndPos = 155; // End position (90 degrees)

// Declare Servo objects
Servo servo1;
Servo servo2;

// Initialize the servos
void servoInit()
{
  servo1.attach(servoPin1); // Attach the first servo to GPIO 18
  servo2.attach(servoPin2); // Attach the second servo to GPIO 19
  Serial.println("Servo control initialized!");
  servo1.write(servoEndPos); // Move the first servo to 90 degrees
  servo2.write(servoEndPos); // Move the second servo to 90 degrees
}

// Run the servo movements
void servoRun()
{
  // Move both servos to 0 degrees
  Serial.println("Moving both servos to 0 degrees");
  servo1.write(servoStartPos); // Move the first servo to 0 degrees
  delay(100);                  // Wait for a second
  servo2.write(servoStartPos); // Move the second servo to 0 degrees
  delay(100);                  // Wait for a second
  onGreen(1);
  delay(500); // Wait for a second
  onGreen(0);
  delay(500);
  onYellow(1);
  delay(500); // Wait for a second
  onYellow(0);
  delay(500);

  // Move both servos to 180 degrees
  Serial.println("Moving both servos to 180 degrees");
  servo1.write(servoEndPos); // Move the first servo to 180 degrees
  delay(100);                // Wait for a second
  servo2.write(servoEndPos); // Move the second servo to 180 degrees
  delay(100); 
  onGreen(1);
               // Wait for a second
}

void doorOpen()
{
  // Move both servos to 0 degrees
  Serial.println("Door open");
  servo1.write(servoStartPos); // Move the first servo to 0 degrees
  delay(100);                  // Wait for a second
  servo2.write(servoStartPos); // Move the second servo to 0 degrees
  delay(100);                  // Wait for a second
}

void doorClose()
{

  Serial.println("Door Close");
  servo1.write(servoEndPos); // Move the first servo to 180 degrees
  delay(100);                // Wait for a second
  servo2.write(servoEndPos); // Move the second servo to 180 degrees
  delay(100);                // Wait for a second
}