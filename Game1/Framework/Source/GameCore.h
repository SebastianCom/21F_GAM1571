#pragma once

namespace fw {

	class GameCore
	{
	public:
		GameCore() {};
		virtual ~GameCore() = 0 {};

		virtual void Update(float deltaTime) {};
		virtual void Draw() {};


	protected:

	};

} // namespace fw
