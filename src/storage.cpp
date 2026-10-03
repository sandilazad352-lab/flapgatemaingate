#include "storage.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#define MAX_FILE_SIZE 1024 // Maximum size for file content to store in a buffer

// Initialize LittleFS
bool littlefsBegin() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
        LittleFS.begin(true) ;
        return false;
    }
    return true;
}

// Write JSON data to a file
bool littlefsWriteJson(const char* path, const JsonDocument& doc) {
    File file = LittleFS.open(path, "w");
    if (!file) {
        Serial.printf("Failed to open file %s for writing\n", path);
        return false;
    }

    // Serialize the JSON document and write it to the file
    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write JSON data");
        file.close();
        return false;
    }

    file.close();
    Serial.printf("Successfully written JSON to %s\n", path);
    return true;
}

// Read JSON data from a file
bool littlefsReadJson(const char* path, JsonDocument& doc) {
    File file = LittleFS.open(path, "r");
    if (!file) {
        Serial.printf("Failed to open file %s for reading\n", path);
        return false;
    }

    // Deserialize the JSON data from the file
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.printf("Failed to parse JSON from file %s: %s\n", path, error.c_str());
        file.close();
        return false;
    }

    file.close();
    return true;
}

// Delete a file
bool littlefsDeleteFile(const char* path) {
    if (LittleFS.remove(path)) {
        Serial.printf("File %s deleted successfully\n", path);
        return true;
    } else {
        Serial.printf("Failed to delete file %s\n", path);
        return false;
    }
}

// Update JSON data in an existing file
bool littlefsUpdateJson(const char* path, const JsonDocument& newDoc) {
    // Read the existing file
    DynamicJsonDocument doc(1024);
    if (!littlefsReadJson(path, doc)) {
        Serial.printf("Failed to read existing JSON from file %s\n", path);
        return false;
    }

    // Modify the JSON data (you can update specific fields here)
    // For example, update a field in the JSON document:
    doc["status"] = newDoc["status"].as<const char*>(); // Example update

    // Write the updated JSON data back to the same file
    if (!littlefsWriteJson(path, doc)) {
        Serial.printf("Failed to write updated JSON to file %s\n", path);
        return false;
    }

    Serial.printf("Successfully updated JSON in %s\n", path);
    return true;
}
