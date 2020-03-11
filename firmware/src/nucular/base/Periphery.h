#pragma once

#include <Arduino.h>
#include <inttypes.h>
#include <pinutils.h>

// -------------------------------------------------------------------------------------------------

struct Periphery
{
    TogglePin led{ LED_BUILTIN }; // D4
    static const uint8_t SPEAKER_ON_OUT_PIN{ D8 };

    void setup();
    void process();
    void setSpeakerEnabled(bool enable);
};
