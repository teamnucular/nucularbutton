#pragma once

#include <Arduino.h>
#include <inttypes.h>
#include <pinutils.h>

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

struct Periphery
{

    //<! enables or disables the speaker output
    static const uint8_t SPEAKER_ON_OUT_PIN{ D8 };

    //<! D4 pin of the secondary controller
    static const uint8_t BUILTIN_LED_OUT_PIN{ LED_BUILTIN };

    void setup();
    void process();
    void enableSpeaker(bool on);
    void enableLed(bool on);
};

} // namespace nucular
