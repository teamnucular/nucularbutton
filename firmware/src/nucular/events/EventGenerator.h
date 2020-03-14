#pragma once

#include "EventTypes.h"
#include <Arduino.h>
#include <elapsedMillis.h>
#include <inttypes.h>

namespace nucular
{

struct EventReceiverInterface;

// ---------------------------------------------------------------------------------------------------------------------

struct EventGenerator
{
    static const uint8_t SWITCH_1_IN_PIN{ D1 };
    static const uint8_t SWITCH_2_IN_PIN{ D5 };
    static const uint8_t SWITCH_3_IN_PIN{ D2 };
    static const uint8_t PUSH_BUTTON_IN_PIN{ D7 };
    static const uint8_t LOADED_IN_PIN{ D6 };

    explicit EventGenerator(EventReceiverInterface &receiver, const uint16_t &process_separation_ms = 100);

    void setup();
    void process();
    const LaunchPanelState &getState() const;

private:
    EventReceiverInterface *event_receiver{ nullptr };
    LaunchPanelState thing_state;
    elapsedMillis elapsed_ms{ 0 };
    uint16_t process_separation_ms{ 1000 };
    const LaunchPanelState &fetchState() const;
    const Event &generateEvent(const LaunchPanelState &new_state) const;
};

} // namespace nucular
