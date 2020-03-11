#include "NucularThing.h"

// -------------------------------------------------------------------------------------------------

NucularThing::NucularThing(EventReceiverInterface &event_receiver)
: event_generator(event_receiver)
{
}

// -------------------------------------------------------------------------------------------------

void NucularThing::setup()
{
    storage.setup();
    storage.loadSettings();

    event_generator.setup();

    base.setup();
    base.setSpeakerEnabled(storage.getIsSpeakerEnabled());
}

// -------------------------------------------------------------------------------------------------

void NucularThing::process()
{
    event_generator.process();
    base.process();
}
