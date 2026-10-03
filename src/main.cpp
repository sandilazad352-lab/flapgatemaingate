#include <Arduino.h>
#include "button.h" // If buttons are used
#include "storage.h"
#include <Ethernet.h>
#include <PubSubClient.h>
#include "mqtt.h"
#include "rfid.h"
#include "servo.h"
#include "voice.h"
#include "light.h"
TaskHandle_t sensorTaskHandle = NULL;

// TaskHandle_t buttonTaskHandle = NULL;
TaskHandle_t ethernetTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t messageTaskHandle = NULL;
VoicePlayer voicePlayer;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC}; // Unique MAC address for your W5500

// W5500 SPI configuration
#define CS_PIN 5 // Chip Select pin for W5500 on AUX-3

// Ethernet and MQTT objects
EthernetClient ethClient ,ethClient2;
PubSubClient mqttClient(ethClient);


void connectEthernet() {
  Serial.println("Connecting to Ethernet...");
  Serial.println("Begin Ethernet");

  Ethernet.init(CS_PIN);  // Use appropriate pin for Ethernet Shield

    IPAddress ip(192,168,1,10);
    IPAddress dns(192, 168, 15, 3);
    IPAddress gw(192,168,1,1);
    IPAddress sn(255, 255, 255, 0);
    Ethernet.begin(mac, ip, dns, gw, sn);
    Serial.println("STATIC OK!");
 // }
  delay(5000);

  Serial.print("Local IP: ");
  Serial.println(Ethernet.localIP());
}

void reconnectEthernet(void *pvParameters)
{
  while (1)
  {
    if (Ethernet.linkStatus() == LinkOFF)
    {
      Serial.println("Ethernet link lost. Reconnecting...");
      onYellow(1);
      delay(500);
      onYellow(0);
      delay(500);
      connectEthernet();
    }
    vTaskDelay(10000 / portTICK_PERIOD_MS); // Delay for task scheduling
  }
}

void setup()
{
  Serial.begin(115200);
  setupLED();
  serialInit();
  littlefsBegin();
  servoInit();
  connectEthernet();
  setupMQTT();

  xTaskCreate(reconnectEthernet, "EthernetTask", 2048 * 4, NULL, 1, &ethernetTaskHandle);
  xTaskCreate(mqttTask, "MqttTask", 2048 * 4, NULL, 1, &mqttTaskHandle);
  xTaskCreatePinnedToCore(messageTask, "MessageTask", 2048 * 4, NULL, 1, &messageTaskHandle, 0);
  xTaskCreatePinnedToCore(serial2Task, "Serial2 Task", 2048, NULL, 1, &serial2TaskHandle, 0);
  xTaskCreatePinnedToCore(serial1Task, "Serial1 Task", 2048, NULL, 1, &serial1TaskHandle, 0);
} 

void loop()
{

}
