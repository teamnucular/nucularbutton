#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "nucular/NuclearLaunchPanel.h"
#include "nucular/events/EventReceiver.h"
#include <HardwareSerial.h>

using nucular::EventReceiver;
using nucular::NuclearLaunchPanel;

// -------------------------------------------------------------------------------------------------

struct SerialReader
{
    SerialReader(NuclearLaunchPanel &nucular_thing) : nucular_thing(nucular_thing) {}

    void setup() { buffered_line.clear(); }
    void process()
    {
        if(!readLine()) return;

        Serial.println();
        if(0 == buffered_line.compareTo("speaker on"))
        {
            nucular_thing.base.enableSpeaker(true);
            nucular_thing.configuration.setIsSpeakerEnabled(true);
            nucular_thing.configuration.saveSettings();
        }
        else if(0 == buffered_line.compareTo("speaker off"))
        {
            nucular_thing.base.enableSpeaker(false);
            nucular_thing.configuration.setIsSpeakerEnabled(false);
            nucular_thing.configuration.saveSettings();
        }
        else if(0 == buffered_line.compareTo("echo off"))
        {
            echo_on = false;
        }
        else if(0 == buffered_line.compareTo("echo on"))
        {
            echo_on = true;
        }
        else if(0 == buffered_line.compareTo("help"))
        {
            Serial.println("supported commands:");
            Serial.print("  Speaker (currently ");
            if(nucular_thing.configuration.getIsSpeakerEnabled())
                Serial.println("[on]):");
            else
                Serial.println("[off]):");

            Serial.println("    speaker on  -   enables the speaker");
            Serial.println("    speaker off -   disables the speaker");

            // -----

            Serial.println("\n");
            Serial.print("  Echo (currently ");
            if(echo_on)
                Serial.println("[on]):");
            else
                Serial.println("[off]):");

            Serial.println("    echo on     - enables console echo");
            Serial.println("    echo off    - disables console echo");
        }
        else
        {
            Serial.println("Unknown command, try help.");
        }

        buffered_line.clear();
    }

    NuclearLaunchPanel &nucular_thing;

protected:
    bool readLine()
    {
        while(Serial.available() > 0)
        {
            char c;
            if(1 == Serial.read(&c, 1))
            {
                if(echo_on) Serial.write(c);
                if((c == '\r' || c == '\n') && buffered_line.length() != 0) return true;
                buffered_line.concat(c);
            }
        }

        return false;
    }

    String buffered_line;
    bool echo_on{ true };
};

// ---------------------------------------------------------------------------------------------------------------------

struct Resources
{
    // -----------------------------------------------------------------------------------------------------------------

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

    // -----------------------------------------------------------------------------------------------------------------

    EventReceiver event_receiver;
    NuclearLaunchPanel nucular_thing{ event_receiver };
    SerialReader serial_reader{ nucular_thing };

    // -----------------------------------------------------------------------------------------------------------------

    void setup()
    {
        Serial.println("Resources::setup");

        //!< wifi off: additional power consumption and radiation leads to erratic behaviour
        WiFi.mode(WIFI_OFF);

        nucular_thing.configuration.setup();
        nucular_thing.configuration.loadSettings();

        nucular_thing.setup();
        nucular_thing.base.enableSpeaker(nucular_thing.configuration.getIsSpeakerEnabled());

        serial_reader.setup();
    }

    // -----------------------------------------------------------------------------------------------------------------

    void process()
    {
        nucular_thing.process();
        serial_reader.process();
    }
} r;

// ---------------------------------------------------------------------------------------------------------------------

void setup() { r.setup(); }

// ---------------------------------------------------------------------------------------------------------------------

void loop() { r.process(); }
