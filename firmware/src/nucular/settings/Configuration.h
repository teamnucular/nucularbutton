#pragma once
#include <SettingsStorage.h>

// ---------------------------------------------------------------------------------------------------------------------

struct Configuration : public SettingsStorage
{
    void setIsSpeakerEnabled(bool is_enabled);
    bool getIsSpeakerEnabled();
};
