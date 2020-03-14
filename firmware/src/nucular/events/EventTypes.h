#pragma once

#include <inttypes.h>

namespace nucular
{

// ---------------------------------------------------------------------------------------------------------------------
// Receiver types

enum class EntityType : uint8_t
{
    Switch1,
    Switch2,
    Switch3,
    LoadedIndicator,
    PushButton,
    Undefined
};

struct Event
{
    EntityType entity{ EntityType ::Undefined };
};

// ---------------------------------------------------------------------------------------------------------------------
// Generator types

enum class SwitchState : uint8_t
{
    On,
    Off,
    Undefined
};

enum class ButtonState : uint8_t
{
    Pressed,
    Released,
    Undefined
};

enum class LoadedState : uint8_t
{
    Loaded,
    Unloaded,
    Undefined
};

template <class T> uint8_t toUint8(const T &t) { return static_cast<uint8_t>(t); }

struct LaunchPanelState
{
    SwitchState switch_1{ SwitchState ::Undefined };
    SwitchState switch_2{ SwitchState ::Undefined };
    SwitchState switch_3{ SwitchState ::Undefined };
    ButtonState push_button{ ButtonState ::Undefined };
    LoadedState loaded_indicator{ LoadedState ::Undefined };
};

} // namespace nucular
