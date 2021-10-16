#pragma once

namespace fw {

	class Event;

	class GameCore
	{
	public:
		GameCore() {};
		virtual ~GameCore() = 0 {};
		
		virtual void OnEvent(Event* pEvent) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
	


	protected:

	};

} // namespace fw
