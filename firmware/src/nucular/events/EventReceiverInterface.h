#pragma once

#include <stdint.h>
#include "EventTypes.h"

struct EventGenerator;

// -------------------------------------------------------------------------------------------------

struct EventReceiverInterface
{
    virtual void takeEvent(const EventGenerator &generator, const Event &event) = 0;
};
