#include "NuclearLaunchPanel.h"

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------

NuclearLaunchPanel::NuclearLaunchPanel(EventReceiverInterface &event_receiver) : event_generator(event_receiver) {}

// ---------------------------------------------------------------------------------------------------------------------

void NuclearLaunchPanel::setup()
{
    configuration.setup();
    configuration.loadSettings();

    event_generator.setup();

    base.setup();
    base.enableSpeaker(configuration.getIsSpeakerEnabled());
}

// ---------------------------------------------------------------------------------------------------------------------

void NuclearLaunchPanel::process()
{
    event_generator.process();
    base.process();
}

} // namespace nucular
