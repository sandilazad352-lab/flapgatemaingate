#ifndef VOICE_H
#define VOICE_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

// VoicePlayer structure
typedef struct {
    SoftwareSerial *voiceSerial;  // Pointer to SoftwareSerial instance
    DFRobotDFPlayerMini  mp3Player; // DFPlayer Mini instance
    uint8_t txPin;               // TX pin for SoftwareSerial
    uint8_t rxPin;               // RX pin for SoftwareSerial
    uint8_t folderNumber;        // Folder number for MP3 files
} VoicePlayer;

// Function prototypes
void VoicePlayer_init(VoicePlayer *player, uint8_t tx, uint8_t rx, uint8_t folder);
void VoicePlayer_begin(VoicePlayer *player);
void VoicePlayer_playFile(VoicePlayer *player, uint8_t fileNumber);
void VoicePlayer_playCondition1(VoicePlayer *player);
void VoicePlayer_playCondition2(VoicePlayer *player);
void VoicePlayer_playCondition3(VoicePlayer *player);
void VoicePlayer_playCondition4(VoicePlayer *player);
void VoicePlayer_playCondition5(VoicePlayer *player);

#endif // VOICE_H
