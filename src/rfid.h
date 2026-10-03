#ifndef RFID_H
#define RFID_H
#include<Arduino.h>
extern char *ptr;


struct RFIDData {
    String id;
    String point;
    int p;
};


extern  String DeviceAdd;


extern RFIDData rfid1Data ,rfid2Data;


// extern String rfid1Data;
// extern String rfid2Data;
extern unsigned long lastCardPunchTime;
extern const unsigned long cardPunchInterval;

// Task handles
extern TaskHandle_t serial2TaskHandle;
extern TaskHandle_t serial1TaskHandle;
extern QueueHandle_t serialQueue; // Declare the queue globally

// Function prototypes
void serial2Task(void *pvParameters);
void serial1Task(void *pvParameters);
String GetCardNo(String cardData);
void serialInit();


#endif