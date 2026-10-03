// #include "sensor.h"

// const int IR_SENSOR_PIN = 34; // Define the sensor pin


// void setupSensorInterrupts()
// {

//     pinMode(IR_SENSOR_PIN, INPUT);
//     // No need for sharp.begin(), just initialize the sensor if needed by the library
// }

// void sensorTask(void *pvParameters)
// {
//     while (true)
//     {
//         float volts = analogRead(IR_SENSOR_PIN) * 0.0008056640625; // value from sensor * (3.3/4096)
//         int distance_cm = 29.988 * pow(volts, -1.173);

     
//          Serial.println(distance_cm);
        
//         vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1 second
//     }
// }
