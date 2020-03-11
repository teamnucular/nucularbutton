#pragma once

#include "events/EventGenerator.h"
#include "nucular/base/Periphery.h"
#include "settings/Settings.h"

// -------------------------------------------------------------------------------------------------


struct NucularThing
{
    EventGenerator event_generator;
    Periphery base;
    Settings storage;

    NucularThing(EventReceiverInterface &event_receiver);
    void setup();
    void process();
};
