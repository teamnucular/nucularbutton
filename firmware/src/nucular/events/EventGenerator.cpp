#include "EventGenerator.h"
#include "EventReceiverInterface.h"

// -------------------------------------------------------------------------------------------------

EventGenerator::EventGenerator(EventReceiverInterface &receiver,
                               const uint16_t &process_separation_ms)
    : event_receiver{&receiver}, process_separation_ms(process_separation_ms) {}

// -------------------------------------------------------------------------------------------------

const ThingState &EventGenerator::getState() const { return thing_state; }

// -------------------------------------------------------------------------------------------------

void EventGenerator::process() {
  if (elapsed_ms >= process_separation_ms) {
    elapsed_ms = 0;

    const ThingState &new_state = fetchState();
    const Event &event = generateEvent(new_state);

    if (EntityType ::Undefined != event.entity) {
      thing_state = new_state;
      if (nullptr != event_receiver) {
        event_receiver->takeEvent(*this, event);
      }
    }
  }
}

// -------------------------------------------------------------------------------------------------

void EventGenerator::setup() {
  pinMode(SWITCH_1_IN_PIN, INPUT);
  pinMode(SWITCH_2_IN_PIN, INPUT);
  pinMode(SWITCH_3_IN_PIN, INPUT);
  pinMode(LOADED_IN_PIN, INPUT);
  pinMode(PUSH_BUTTON_IN_PIN, INPUT);
}

// -------------------------------------------------------------------------------------------------

const ThingState &EventGenerator::fetchState() const {
  static ThingState state_cache;

  const uint8_t on = 0;
  state_cache.switch_1 = (digitalRead(SWITCH_1_IN_PIN) == on) ? SwitchState ::On
                                                             : SwitchState ::Off;
  state_cache.switch_2 = (digitalRead(SWITCH_2_IN_PIN) == on) ? SwitchState ::On
                                                             : SwitchState ::Off;
  state_cache.switch_3 = (digitalRead(SWITCH_3_IN_PIN) == on) ? SwitchState ::On
                                                             : SwitchState ::Off;
  state_cache.loaded_indicator = (digitalRead(LOADED_IN_PIN) == on)
                                 ? LoadedState ::Loaded
                                 : LoadedState::Unloaded;
  state_cache.push_button = (digitalRead(PUSH_BUTTON_IN_PIN) == on)
                            ? ButtonState ::Pressed
                            : ButtonState ::Released;

  return state_cache;
}

// -------------------------------------------------------------------------------------------------

const Event &EventGenerator::generateEvent(const ThingState &new_state) const {
  static Event current_event;

  if (thing_state.switch_1 != new_state.switch_1) {
    current_event.entity = EntityType ::Switch1;
  } else if (thing_state.switch_2 != new_state.switch_2) {
    current_event.entity = EntityType ::Switch2;
  } else if (thing_state.switch_3 != new_state.switch_3) {
    current_event.entity = EntityType ::Switch3;
  } else if (thing_state.loaded_indicator != new_state.loaded_indicator) {
    current_event.entity = EntityType ::LoadedIndicator;
  } else if (thing_state.push_button != new_state.push_button) {
    current_event.entity = EntityType ::NucularButton;
  } else {
    current_event.entity = EntityType ::Undefined;
  }

  return current_event;
}
