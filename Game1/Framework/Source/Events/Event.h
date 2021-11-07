#pragma once

#include "Math/Vector.h"
#include "Framework.h"

namespace fw {

enum class EventType { Input, NotSet, Collision, RoundEnd };
enum class DeviceType { Keyboard, Mouse };
enum class InputState { Pressed, Released };
enum class CollisionType {EnemyOnObject, PlayerOnObject, BulletOnObject, BulletOnWall};

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

class Collision : public Event
{
public:
    Collision(CollisionType type, GameObject* CollidedObject1, GameObject* CollidedObject2)
    {
        m_CollisionType = type;
        m_Collided1 = CollidedObject1;
        m_Collided2 = CollidedObject2;
    }
    ~Collision() {}

    virtual EventType GetEventType() override { return EventType::Collision; }
    CollisionType GetCollisionType() { return m_CollisionType; }
    GameObject* GetCollidedObject1() { return m_Collided1; }
    GameObject* GetCollidedObject2() { return m_Collided2; }

protected:
   CollisionType m_CollisionType;
   GameObject* m_Collided1;
   GameObject* m_Collided2;
};

class RoundEnd : public Event
{
public:
    RoundEnd()
    {
        
    }
    ~RoundEnd() {}

    virtual EventType GetEventType() override { return EventType::RoundEnd; }
    

protected:

};

} // namespace fw
