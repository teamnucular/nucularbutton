#pragma once

#include "base/Periphery.h"
#include "events/EventGenerator.h"
#include "settings/Configuration.h"

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

struct NuclearLaunchPanel
{

    explicit NuclearLaunchPanel(EventReceiverInterface &event_receiver);
    void setup();
    void process();

    //!< generates events if switch/button/indicator state changes
    EventGenerator event_generator;

    //!< interface to speaker, and build in led (of secondary micro controller)
    Periphery base;

    //!< persistent configuration
    Configuration configuration;
};

} // namespace nucular
