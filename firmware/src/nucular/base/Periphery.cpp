#include "Periphery.h"

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

void Periphery::setup()
{
    pinMode(BUILTIN_LED_OUT_PIN, OUTPUT);
    pinMode(SPEAKER_ON_OUT_PIN, OUTPUT);
}

// ---------------------------------------------------------------------------------------------------------------------

void Periphery::process() {}

// ---------------------------------------------------------------------------------------------------------------------

void Periphery::enableSpeaker(bool on) { digitalWrite(SPEAKER_ON_OUT_PIN, (on) ? HIGH : LOW); }

// ---------------------------------------------------------------------------------------------------------------------

void Periphery::enableLed(bool on)
{
    //!< LOW => LED on, HIGH => LED off
    digitalWrite(BUILTIN_LED_OUT_PIN, (on) ? LOW : HIGH);
}

} // namespace nucular
