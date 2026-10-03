#include "light.h"

void setupLED()
{

    pinMode(GREEN_PIN, OUTPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
}
void onGreen(int onOff)
{
    if (onOff)
    {
        digitalWrite(GREEN_PIN, HIGH);
    }
    else
    {
        digitalWrite(GREEN_PIN, LOW);
    }
}
void onRed(int onOff)
{
    if (onOff)
    {
        digitalWrite(RED_PIN, HIGH);
    }
    else
    {
        digitalWrite(RED_PIN, LOW);
    }
}
void onYellow(int onOff)
{
    if (onOff)
    {
        digitalWrite(YELLOW_PIN, HIGH);
    }
    else
    {
        digitalWrite(YELLOW_PIN, LOW);
    }
}