// #include "button.h"

// // Initialize button state flags
// volatile bool startButtonPressed = false;
// volatile bool stopButtonPressed = false;
// volatile bool limitSwitchTriggered = false;

// // ISR for Start button
// void IRAM_ATTR handleStartButton() {
//   startButtonPressed = true;  // Set Start button flag
// }

// // ISR for Stop button
// void IRAM_ATTR handleStopButton() {
//   stopButtonPressed = true;   // Set Stop button flag
// }

// // ISR for Limit switch
// void IRAM_ATTR handleLimitSwitch() {
//   limitSwitchTriggered = true;  // Set Limit switch flag
// }

// // Setup function to configure buttons and interrupts
// void setupButtonInterrupts() {
//   // Configure button pins as input with pull-up resistors
//   pinMode(START_BUTTON_PIN, INPUT_PULLUP);
//   pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
//   pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

//   // Attach interrupts to the pins
//   attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN), handleStartButton, FALLING);
//   attachInterrupt(digitalPinToInterrupt(STOP_BUTTON_PIN), handleStopButton, FALLING);
//   attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_PIN), handleLimitSwitch, FALLING);
// }



// void buttonTask(void *pvParameters) {
//   while (1) {
//     // Check Start button press
//     if (startButtonPressed) {
//       startButtonPressed = false; // Clear the flag
//       Serial.println("Start button pressed!");
//       digitalWrite(LED_PIN, HIGH); // Example action
//     }

//     // Handle Stop button press
//     if (stopButtonPressed) {
//       stopButtonPressed = false; // Clear the flag
//       Serial.println("Stop button pressed!");
//       digitalWrite(LED_PIN, LOW); // Example action
//     }

//     // Handle Limit switch trigger
//     if (limitSwitchTriggered) {
//       limitSwitchTriggered = false; // Clear the flag
//       Serial.println("Limit switch triggered!");
//       // Add specific logic for the Limit switch
//     }

//     vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for task scheduling
//   }
// }