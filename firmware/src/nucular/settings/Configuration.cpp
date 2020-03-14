#include "Configuration.h"

// ---------------------------------------------------------------------------------------------------------------------

void Configuration::setIsSpeakerEnabled(bool is_enabled)
{
    auto node = getDocumentRoot().getOrAddMember("is_speaker_enabled");
    node.set(is_enabled);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Configuration::getIsSpeakerEnabled()
{
    auto node = getDocumentRoot().getMember("is_speaker_enabled");

    if(node.isNull()) { setIsSpeakerEnabled(false); }

    node = getDocumentRoot().getMember("is_speaker_enabled");

    return node.as<bool>();
}
