#pragma once

#include <HardwareSerial.h>
#include "EventReceiverInterface.h"

// -------------------------------------------------------------------------------------------------

struct EventReceiver : public EventReceiverInterface
{
    void takeEvent(const EventGenerator &generator, const Event &event) override;
};