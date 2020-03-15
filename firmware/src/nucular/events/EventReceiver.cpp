#include "EventReceiver.h"
#include "EventGenerator.h"

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

void EventReceiver::onEvent(const EventGenerator &generator, const Event &event)
{
    LaunchPanelState state = generator.getState();
    Serial.printf("{"
                  "\"event\": \"%d\", "
                  "\"state\": {"
                  "\"switch_1\": \"%d\" , "
                  "\"switch_2\": \"%d\", "
                  "\"switch_3\": \"%d\", "
                  "\"loaded_indicator\": \"%d\", "
                  "\"push_button\": \"%d\""
                  "}}\r\n",
                  toUint8(event.entity), toUint8(state.switch_1), toUint8(state.switch_2), toUint8(state.switch_3),
                  toUint8(state.loaded_indicator), toUint8(state.push_button));
}

} // namespace nucular
