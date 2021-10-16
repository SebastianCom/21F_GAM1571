#include "CoreHeaders.h"
#include "EventManager.h"
#include "Event.h"
#include "GameCore.h"

namespace fw {

EventManager::EventManager()
	: m_pGameCore(nullptr)
{
}

EventManager::~EventManager()
{
	while (m_EventQueue.empty() == false)
	{
		delete m_EventQueue.front();
		m_EventQueue.pop();
	}
}

void EventManager::AddEvent(Event* pEvent)
{
	m_EventQueue.push(pEvent);
}

void EventManager::ProcessEvents()
{
	while (m_EventQueue.empty() == false)
	{
		Event* pEvent = m_EventQueue.front();
		m_EventQueue.pop();

		m_pGameCore->OnEvent(pEvent);
		delete pEvent;
	}
}

void EventManager::SetGameCore(GameCore* pgameCore)
{
	m_pGameCore = pgameCore;
}

} // namespace fw
