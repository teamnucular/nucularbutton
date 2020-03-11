#pragma once
#include <SettingsStorage.h>

// -------------------------------------------------------------------------------------------------

struct Settings : public SettingsStorage
{
    void setIsSpeakerEnabled(bool is_enabled);
    bool getIsSpeakerEnabled();
};
