#include "Periphery.h"

// -------------------------------------------------------------------------------------------------

void Periphery::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // led off

    pinMode(SPEAKER_ON_OUT_PIN, OUTPUT);
    setSpeakerEnabled(false);
}

// -------------------------------------------------------------------------------------------------

void Periphery::process() {}

// -------------------------------------------------------------------------------------------------

void Periphery::setSpeakerEnabled(bool enable)
{
    if(enable)
    {
        digitalWrite(SPEAKER_ON_OUT_PIN, 1);
        return;
    }
    digitalWrite(SPEAKER_ON_OUT_PIN, 0);
}
