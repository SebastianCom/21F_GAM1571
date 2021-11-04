#pragma once

#include "Math/Vector.h"
#include "Framework.h"

namespace fw {

enum class EventType { Input, NotSet, Collision };
enum class DeviceType { Keyboard, Mouse };
enum class InputState { Pressed, Released };

class Event
{
public:
    Event() {}
    virtual ~Event() {}
    virtual EventType GetEventType() = 0;
};

class InputEvent : public Event
{
public:
    InputEvent(DeviceType device, InputState state, int id)
        : m_DeviceType(device)
        , m_InputState(state)
        , m_ID(id)
        , m_Position( 0, 0 )
    {
    }
    virtual ~InputEvent() {}

    virtual EventType GetEventType() override { return EventType::Input; }

    DeviceType GetInputDeviceType() { return m_DeviceType; }
    InputState GetInputState() { return m_InputState; }
    int GetID() { return m_ID; }

protected:
    DeviceType m_DeviceType;
    InputState m_InputState;
    int m_ID;
    vec2 m_Position;
};

class CollisionEvent : public Event
{
public:
    CollisionEvent()
    {

    }
    ~CollisionEvent() {}

    virtual EventType GetEventType() override { return EventType::Collision; }


protected:

};

} // namespace fw
