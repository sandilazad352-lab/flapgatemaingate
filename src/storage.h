// LittleFSHandler.h
#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

// Define the maximum file size for the content buffer
#define MAX_FILE_SIZE 1024 // Maximum size for file content to store in a buffer

// Initialize LittleFS filesystem
bool littlefsBegin();

// Write JSON data to a file
bool littlefsWriteJson(const char* path, const JsonDocument& doc);

// Read JSON data from a file
bool littlefsReadJson(const char* path, JsonDocument& doc);

// Delete a file
bool littlefsDeleteFile(const char* path);

// Update JSON data in an existing file
bool littlefsUpdateJson(const char* path, const JsonDocument& newDoc);

#endif // STORAGE_H
