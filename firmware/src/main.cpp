#include "nucular/NucularThing.h"
#include "nucular/events/EventReceiver.h"
#include <HardwareSerial.h>



// -------------------------------------------------------------------------------------------------

struct SerialReader
{
    SerialReader(NucularThing &nucular_thing)
    : nucular_thing(nucular_thing)
    {
    }

    void setup() {}
    void process()
    {
        if(Serial.available() > 0)
        {
            String in = Serial.readStringUntil('\n');
            in.trim();

            if(0 == in.compareTo("speaker on"))
            {
                nucular_thing.base.setSpeakerEnabled(true);
                nucular_thing.storage.setIsSpeakerEnabled(true);
            }
            else if(0 == in.compareTo("speaker off"))
            {
                nucular_thing.base.setSpeakerEnabled(false);
                nucular_thing.storage.setIsSpeakerEnabled(false);
            }
            else if(0 == in.compareTo("help"))
            {
                Serial.println("supported commands:");
                Serial.println("  speaker on   -   enables the speaker");
                Serial.println("  speaker off  -   disables the speaker");
            }
            else
            {
                Serial.println("SerialReader::process: Unknown command, try help.");
            }
        }
    }

    NucularThing &nucular_thing;

};

// -------------------------------------------------------------------------------------------------

struct Resources
{
    // ---------------------------------------------------------------------------------------------

    struct EarlyInitializer
    {
        EarlyInitializer()
        {
            Serial.begin(230400);
            while(!Serial)
                delay(10);
            Serial.printf("\n\n\n");
            Serial.println("Resources::EarlyInitializer");
        }
    } _;

    // ---------------------------------------------------------------------------------------------

    EventReceiver event_receiver;
    NucularThing nucular_thing{ event_receiver };
    SerialReader serial_reader{nucular_thing};

    // ---------------------------------------------------------------------------------------------

    void setup()
    {
        Serial.println("Resources::setup");

        nucular_thing.storage.setup();
        nucular_thing.storage.loadSettings();

        nucular_thing.setup();
        nucular_thing.base.setSpeakerEnabled(nucular_thing.storage.getIsSpeakerEnabled());

        serial_reader.setup();
    }

    // ---------------------------------------------------------------------------------------------

    void process()
    {
        nucular_thing.process();
        serial_reader.process();
    }
} r;

// -------------------------------------------------------------------------------------------------

void setup() { r.setup(); }

// -------------------------------------------------------------------------------------------------

void loop() { r.process(); }
