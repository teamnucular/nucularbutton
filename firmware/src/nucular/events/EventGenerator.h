#pragma once

#include "EventTypes.h"
#include <Arduino.h>
#include <elapsedMillis.h>
#include <inttypes.h>

struct EventReceiverInterface;

// -------------------------------------------------------------------------------------------------

struct EventGenerator {
  static const uint8_t SWITCH_1_IN_PIN{D1};
  static const uint8_t SWITCH_2_IN_PIN{D5};
  static const uint8_t SWITCH_3_IN_PIN{D2};
  static const uint8_t PUSH_BUTTON_IN_PIN{D7};
  static const uint8_t LOADED_IN_PIN{D6};

  explicit EventGenerator(EventReceiverInterface &receiver,
                          const uint16_t &process_separation_ms = 100);

  void setup();
  void process();
  const ThingState &getState() const;

private:
  EventReceiverInterface *event_receiver{nullptr};
  ThingState thing_state;
  elapsedMillis elapsed_ms{0};
  uint16_t process_separation_ms{1000};
  const ThingState &fetchState() const;
  const Event &generateEvent(const ThingState &new_state) const;
};
