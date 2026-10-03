#include "mqtt.h"
#include "light.h"

// MQTT topics
String mqttTopicSend = "flapgate/s/" + DeviceAdd;
String mqttTopicReceive = "flapgate/r/" + DeviceAdd;
 String mqttTopicDoorOpenClose = "flapgate/r/dooroc/" + DeviceAdd;
// MQTT broker settings
IPAddress mqttServer(172, 16, 16, 4);

// Callback for handling received MQTT messages
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");

  String message = "";
  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Handle different topics with different logic
  if (String(topic) == mqttTopicReceive)
  {
    if (message == "1")
    {
      Serial.println(message);
      servoRun();
    }
    else
    {
      Serial.println(message);
      onRed(1);
      delay(2000);
      onRed(0);
      delay(500);
    }
  }
  else if (String(topic) == mqttTopicDoorOpenClose)
  {
    if (message == "1")
    {
      doorOpen();
    }
    else
    {
      doorClose();
    }
  }
  else if (String(topic) == "topic/command3")
  {
    if (message == "3")
    {
      Serial.println("Command 3 received on topic/command3!");
    }
    else
    {
      Serial.println("Invalid command on topic/command3");
    }
  }
  else
  {
    Serial.println("Unknown topic received.");
  }
}

// Initialize MQTT connection
void setupMQTT()
{
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(mqttCallback);
}

// Reconnect MQTT if disconnected
void reconnectMQTT()
{
  while (!mqttClient.connected())
  {
    Serial.println("Connecting to MQTT broker...");
    String clientId = "ArduinoClient-";
    clientId += String(micros() % 1000);

    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("MQTT connected!");
      mqttClient.subscribe(mqttTopicReceive.c_str());
      mqttClient.subscribe(mqttTopicDoorOpenClose.c_str());
      onGreen(1);
    }
    else
    {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(". Retrying in 5 seconds...");
      onGreen(0);
      delay(100);
      onYellow(1);
      delay(500);
      onYellow(0);
      delay(500);
      delay(5000);
    }
  }
}

// Publish a message to the MQTT server
void sendMQTTMessage(RFIDData Data)
{
  StaticJsonDocument<256> doc;
  doc["point"] = Data.point;
  doc["device_add"] = DeviceAdd;
  doc["rfid"] = Data.id;
  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  if (!Data.id.equals("00000000"))
  {
    mqttClient.publish(mqttTopicSend.c_str(), jsonBuffer);
  }
}

void mqttTask(void *pvParameters)
{
  while (1)
  {
    // Maintain MQTT connection
    if (!mqttClient.connected())
    {
      reconnectMQTT();
    }
    // Handle MQTT loop
    mqttClient.loop();

    vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for task scheduling
  }
}

void messageTask(void *pvParameters)
{
  while (true)
  {
    RFIDData receivedData;

    // Wait for data from the queue
    if (xQueueReceive(serialQueue, &receivedData, portMAX_DELAY) == pdTRUE)
    {
      Serial.print("MessageTask received data: ");
      sendMQTTMessage(receivedData);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Yield to other tasks
  }
}

void rfidSendToServer(String data)
{

  StaticJsonDocument<200> rfid_doc;
  rfid_doc["cmd"] = 200; // for rfid code 100
  rfid_doc["device_add"] = "flap_gate_01";
  rfid_doc["rfid"] = data;
  char rfid_json[200];
  serializeJson(rfid_doc, rfid_json);
  mqttClient.publish(mqttTopicSend.c_str(), rfid_json);
}
