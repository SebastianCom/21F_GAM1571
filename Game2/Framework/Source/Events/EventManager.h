#pragma once

namespace fw {

class Event;
class GameCore;

class EventManager
{
public:
    EventManager();
    virtual ~EventManager();

    void AddEvent(Event* pEvent);
    void ProcessEvents();

    void SetGameCore(GameCore* pGameCore);

protected:
    GameCore* m_pGameCore;

    std::queue<Event*> m_EventQueue;
};

} // namespace fw
