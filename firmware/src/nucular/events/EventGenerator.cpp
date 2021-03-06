#include "EventGenerator.h"
#include "EventReceiverInterface.h"

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

EventGenerator::EventGenerator(EventReceiverInterface &receiver, const uint16_t &process_separation_ms)
: event_receiver{ &receiver }, process_separation_ms(process_separation_ms)
{
}

// ---------------------------------------------------------------------------------------------------------------------

const LaunchPanelState &EventGenerator::getState() const { return current_state; }

// ---------------------------------------------------------------------------------------------------------------------

void EventGenerator::process()
{
    if(elapsed_ms >= process_separation_ms)
    {
        elapsed_ms = 0;

        const LaunchPanelState &new_state = fetchState();
        const Event &event = generateEvent(new_state);

        if(EntityType ::Undefined != event.entity)
        {
            current_state = new_state;
            if(nullptr != event_receiver) { event_receiver->onEvent(*this, event); }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void EventGenerator::setup()
{
    pinMode(SWITCH_1_IN_PIN, INPUT);
    pinMode(SWITCH_2_IN_PIN, INPUT);
    pinMode(SWITCH_3_IN_PIN, INPUT);
    pinMode(LOADED_IN_PIN, INPUT);
    pinMode(PUSH_BUTTON_IN_PIN, INPUT);
}

// ---------------------------------------------------------------------------------------------------------------------

const LaunchPanelState &EventGenerator::fetchState() const
{
    static LaunchPanelState state_cache;

    const uint8_t on = 0;
    state_cache.switch_1 = (digitalRead(SWITCH_1_IN_PIN) == on) ? SwitchState ::On : SwitchState ::Off;
    state_cache.switch_2 = (digitalRead(SWITCH_2_IN_PIN) == on) ? SwitchState ::On : SwitchState ::Off;
    state_cache.switch_3 = (digitalRead(SWITCH_3_IN_PIN) == on) ? SwitchState ::On : SwitchState ::Off;
    state_cache.loaded_indicator = (digitalRead(LOADED_IN_PIN) == on) ? LoadedState ::Loaded : LoadedState::Unloaded;
    state_cache.push_button = (digitalRead(PUSH_BUTTON_IN_PIN) == on) ? ButtonState ::Pressed : ButtonState ::Released;

    return state_cache;
}

// ---------------------------------------------------------------------------------------------------------------------

const Event &EventGenerator::generateEvent(const LaunchPanelState &new_state) const
{
    static Event current_event;

    // ensure priority: push button over switch 3 over loaded indicator over switch 2 over switch 1

    if(current_state.push_button != new_state.push_button) { current_event.entity = EntityType ::PushButton; }

    else if(current_state.switch_3 != new_state.switch_3)
    {
        // note: since EntityType::Switch3 and EntityType::LoadedIndicator occur with a slight time separation,
        // in most cases the EntityType::Switch3 event overwrites the EntityType::LoadedIndicator (which is acceptable)
        current_event.entity = EntityType ::Switch3;
    }

    else if(current_state.loaded_indicator != new_state.loaded_indicator)
    {
        current_event.entity = EntityType ::LoadedIndicator;
    }

    else if(current_state.switch_2 != new_state.switch_2)
    {
        current_event.entity = EntityType ::Switch2;
    }

    else if(current_state.switch_1 != new_state.switch_1)
    {
        current_event.entity = EntityType ::Switch1;
    }

    else
    {
        current_event.entity = EntityType ::Undefined;
    }

    return current_event;
}

} // namespace nucular
