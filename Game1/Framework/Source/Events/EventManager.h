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
    
    void SetGameCore(GameCore* pgameCore);
protected:
    std::queue<Event*> m_EventQueue;
    GameCore* m_pGameCore;
};

} // namespace fw
