#include "voice.h"

void VoicePlayer_init(VoicePlayer *player, uint8_t tx, uint8_t rx, uint8_t folder)
{
    // Initialize SoftwareSerial dynamically
    player->voiceSerial = new SoftwareSerial(rx, tx);
    player->txPin = tx;
    player->rxPin = rx;
    player->folderNumber = folder;
}

void VoicePlayer_begin(VoicePlayer *player)
{
    // Start SoftwareSerial
    player->voiceSerial->begin(9600);

    // Initialize DFPlayer Mini
    if (!player->mp3Player.begin(*(player->voiceSerial), true, true))
    {
        Serial.println("DFPlayer initialization failed!");
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
    }
    else
    {
        Serial.println("DFPlayer initialized successfully.");
    }
}

void VoicePlayer_playFile(VoicePlayer *player, uint8_t fileNumber)
{
    player->mp3Player.playFolder(player->folderNumber, fileNumber);
}

void VoicePlayer_playCondition1(VoicePlayer *player)
{
    VoicePlayer_playFile(player, 1);
}

void VoicePlayer_playCondition2(VoicePlayer *player)
{
    VoicePlayer_playFile(player, 2);
}

void VoicePlayer_playCondition3(VoicePlayer *player)
{
    VoicePlayer_playFile(player, 3);
}

void VoicePlayer_playCondition4(VoicePlayer *player)
{
    VoicePlayer_playFile(player, 4);
}

void VoicePlayer_playCondition5(VoicePlayer *player)
{
    VoicePlayer_playFile(player, 5);
}


