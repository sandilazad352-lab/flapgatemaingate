#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "rfid.h"
#include <servo.h>

// MQTT topics
extern String mqttTopicSend;
extern String mqttTopicReceive;
extern String mqttTopicDoorOpenClose;
extern String mqttTopicReceive;

// MQTT broker settings
extern IPAddress mqttServer;
extern PubSubClient mqttClient;

// Function declarations
void setupMQTT();
void reconnectMQTT();
void mqttCallback(char *topic, byte *payload, unsigned int length);
void sendMQTTMessage(RFIDData Data);
void mqttTask(void *pvParameters);
void messageTask(void *pvParameters);
void rfidSendToServer(String data);


#endif // MQTT_HANDLER_H
