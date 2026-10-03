#include <rfid.h>
char *ptr = NULL;
String rfidData = "";
String serial1Data = "";
unsigned long lastCardPunchTime = 0;
const unsigned long cardPunchInterval = 5000; // 5 seconds

String DeviceAdd = "fg001";
RFIDData rfid1Data, rfid2Data;

#define RX1_PIN 16 // Change to your desired RX pin
#define TX1_PIN -1 // Change to your desired TX pin

#define RX2_PIN 4  // Change to your desired RX pin
#define TX2_PIN -1 // Change to your desired TX pin

TaskHandle_t serial2TaskHandle = NULL;
TaskHandle_t serial1TaskHandle = NULL;

void serialInit()
{
  Serial1.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN);
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

// Create a queue to pass messages between tasks
QueueHandle_t serialQueue = xQueueCreate(1, sizeof(RFIDData));


void serial2Task(void *pvParameters)
{
  while (true)
  {
    // Read data from Serial2 if available
    while (Serial2.available() > 0)
    {
      char c = Serial2.read();
      rfidData += String(c, HEX) + ","; // Append the hex value to the string
    }

    // Process the accumulated data
    if (rfidData.length() > 5) // Ensure there's valid data
    {
      unsigned long currentMillis = millis(); // Get the current time

      // Check if 5 seconds have passed since the last card punch
      if (currentMillis - lastCardPunchTime >= cardPunchInterval)
      {
        rfid2Data.id = GetCardNo(rfidData); // Process the RFID data
        rfid2Data.point = "exit";
        // Clear the string after processing
        xQueueSend(serialQueue, &rfid2Data, portMAX_DELAY); // Send data to the queue
        // rfidData = ""; // Clear the string to prevent reprocessing the same data
        lastCardPunchTime = currentMillis; // Update the last punch time
      }
      else
      {
        Serial.println("Serial2 card punch ignored: Try again after 5 seconds.");
        rfidData = ""; // Clear the string to prevent reprocessing the same data
      }
    }

    // Yield to other tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void serial1Task(void *pvParameters)
{
  while (true)
  {
    // Read data from Serial1 if available
    while (Serial1.available() > 0)
    {
      char c = Serial1.read();
      serial1Data += String(c, HEX) + ","; // Append the hex value to the string
    }

    // Process the accumulated data
    if (serial1Data.length() > 5) // Ensure there's valid data
    {
      unsigned long currentMillis = millis(); // Get the current time

      // Check if 5 seconds have passed since the last card punch
      if (currentMillis - lastCardPunchTime >= cardPunchInterval)
      {
        rfid1Data.id = GetCardNo(serial1Data); // Process the RFID data
        rfid1Data.point = "entry";
        xQueueSend(serialQueue, &rfid1Data, portMAX_DELAY); // Send data to the queue
        serial1Data = "";
        lastCardPunchTime = currentMillis; // Update the last punch time
      }
      else
      {
        Serial.println("Serial1 card punch ignored: Try again after 5 seconds.");
        serial1Data = ""; // Clear the string to prevent reprocessing the same data
      }
    }

    // Yield to other tasks
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

String GetCardNo(String cardData)
{
  String index4 = "", index5 = "", index6 = "";
  byte index = 0;
  String str = cardData;
  char array[str.length() + 1];
  strcpy(array, str.c_str());

  ptr = strtok(array, ","); // delimiter
  while (ptr != NULL)
  {
    String Add = "";
    int a = 0;
    int length = 2 - strlen(ptr);
    while (a < length)
    {
      Add += "0";
      a++;
    }

    if (index == 4)
    {
      index4 = Add + String(ptr);
    }
    if (index == 5)
    {
      index5 = Add + String(ptr);
    }
    if (index == 6)
    {
      index6 = Add + String(ptr);
    }

    index++;
    ptr = strtok(NULL, ",");
  }

  String hex = index4 + index5 + index6;
  String AddValue = "", AddValue2 = "", AddValue3 = "";
  int x = 0;
  int length = 10 - hex.length();
  while (x < length)
  {
    AddValue += "0";
    x++;
  }
  String initValue = AddValue + hex;
  String F = initValue.substring(0, 6);
  String L = initValue.substring(6, 10);

  int ss;
  char *endptr;
  ss = strtol(F.c_str(), &endptr, 16);
  int sss;
  char *endptrr;
  sss = strtol(L.c_str(), &endptrr, 16);

  int decValue = (ss, DEC);
  int decValue2 = (sss, DEC);

  int FL = 3 - ((String(ss, DEC))).length();
  int k = 0;
  while (k < FL)
  {
    AddValue2 += "0";
    k++;
  }
  String initValue1 = AddValue2 + String(ss, DEC);

  int LV = 5 - ((String(sss, DEC))).length();
  int r = 0;
  while (r < LV)
  {
    AddValue3 += "0";
    r++;
  }
  String initValue2 = AddValue3 + String(sss, DEC);
  String Value = initValue1 + initValue2;

  return Value;

}