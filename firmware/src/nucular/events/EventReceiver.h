#pragma once

#include "EventReceiverInterface.h"
#include <HardwareSerial.h>

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

struct EventReceiver : public EventReceiverInterface
{
    void onEvent(const EventGenerator &generator, const Event &event) override;
};

} // namespace nucular
