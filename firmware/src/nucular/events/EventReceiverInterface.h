#pragma once

#include "EventTypes.h"
#include <stdint.h>

namespace nucular
{

struct EventGenerator;

// ---------------------------------------------------------------------------------------------------------------------

struct EventReceiverInterface
{
    virtual void onEvent(const EventGenerator &generator, const Event &event) = 0;
};

} // namespace nucular
