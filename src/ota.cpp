// #include "ota.h"

// void update(String ota_server, int port, String versionCheck, String path, String deviceAdd, String mqttTopic)
// {
//     StaticJsonDocument<256> doc;
//     String jsonMessage;

//     doc["cmd"] = 105;
//     doc["deviceadd"] = deviceAdd;

//     httpUpdate.rebootOnUpdate(false); // Disable automatic reboot after update
//     hideCheck = true;

//     Serial.println(F("Starting update..."));

//     unsigned long lastRetryMillis = 0;
//     const unsigned long retryInterval = 10000; // Retry every 10 seconds
//     int retryCount = 0;
//     const int maxRetries = 3;

//     while (retryCount < maxRetries)
//     {
//         unsigned long currentMillis = millis();

//         // Check if retry interval has elapsed
//         if (currentMillis - lastRetryMillis >= retryInterval || retryCount == 0)
//         {
//             lastRetryMillis = currentMillis;
//             t_httpUpdate_return ret = httpUpdate.update(ethClient2, ota_server, port, &path);

//             switch (ret)
//             {
//             case HTTP_UPDATE_FAILED:
//                 Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n",
//                               httpUpdate.getLastError(),
//                               httpUpdate.getLastErrorString().c_str());
//                 doc["status"] = 0;
//                 doc["description"] = "Update Failed";
//                 doc["version"] = versionCheck;
//                 serializeJson(doc, jsonMessage);
//                 mqttClient.publish(mqttTopic.c_str(), jsonMessage.c_str());
//                 retryCount++;
//                 break;

//             case HTTP_UPDATE_NO_UPDATES:
//                 Serial.println(F("No updates available."));
//                 doc["status"] = 2;
//                 doc["description"] = "No updates available";
//                 serializeJson(doc, jsonMessage);
//                 mqttClient.publish(mqttTopic.c_str(), jsonMessage.c_str());
//                 return;

//             case HTTP_UPDATE_OK:
//                 Serial.println(F("Update successful!"));
//                 doc["status"] = 1;
//                 doc["description"] = "Update successful!";
//                 doc["version"] = versionCheck;
//                 serializeJson(doc, jsonMessage);
//                 mqttClient.publish(mqttTopic.c_str(), jsonMessage.c_str());
//                 ESP.restart(); // Restart to apply the update
//                 return;
//             }
//         }
//     }

//     Serial.println(F("Max retries reached. Update failed."));
// }
